#!/usr/bin/env python3
import argparse
import re
import sys
from bisect import bisect_right
from dataclasses import dataclass
from typing import List, Optional, Tuple


@dataclass(frozen=True)
class Sym:
    addr: int
    name: str


STACK_RE = re.compile(
    r"^\s*\[SP\+0x(?P<spoff>[0-9A-Fa-f]+)\]\s+RA=0x(?P<ra>[0-9A-Fa-f]+)\s+\(pc=0x(?P<pc>[0-9A-Fa-f]+)\)\s*$"
)

HEXADDR_RE = re.compile(r"0x[0-9A-Fa-f]+")


def parse_stack_dump(text: str) -> List[Tuple[int, int, int]]:
    """
    Returns list of tuples: (sp_offset, ra, pc)
    """
    out = []
    for line in text.splitlines():
        m = STACK_RE.match(line)
        if not m:
            continue
        spoff = int(m.group("spoff"), 16)
        ra = int(m.group("ra"), 16)
        pc = int(m.group("pc"), 16)
        out.append((spoff, ra, pc))
    return out


def is_plausible_symbol_name(name: str) -> bool:
    # Filter out section markers / noise commonly present in map files
    if not name:
        return False
    if name.startswith("."):
        return False
    if name in ("*", "LOAD", "START", "END"):
        return False
    # Common map noise tokens:
    if name in ("fill", "ALIGN", "COMMON"):
        return False
    return True


def parse_map_symbols(map_text: str) -> List[Sym]:
    """
    Tries to extract (address, symbol) pairs from a GNU ld map file.

    We accept multiple common patterns, e.g.
      0x34183c6c                touchgfx::foo()
      0x34183c6c                _ZN8touchgfx...
      .text.somefunc  0x34183c6c  0x34  file.o
      0x34183c6c                __aeabi_memcpy

    Strategy:
      - tokenize each line
      - find first hex address token
      - pick a likely symbol token after it
    """
    syms = []
    for line in map_text.splitlines():
        # quick reject if no 0x...
        if "0x" not in line:
            continue

        # Split into tokens but preserve order
        tokens = line.strip().split()
        if not tokens:
            continue

        # Find first token that looks like an address
        addr_idx = None
        addr = None
        for i, t in enumerate(tokens):
            if t.startswith("0x") and HEXADDR_RE.fullmatch(t):
                try:
                    addr = int(t, 16)
                    addr_idx = i
                    break
                except ValueError:
                    pass
        if addr_idx is None or addr is None:
            continue

        # Candidate symbol token is usually next token (or sometimes later)
        # Skip size tokens (0xNN or decimal) and object file names.
        cand = None
        for j in range(addr_idx + 1, min(addr_idx + 6, len(tokens))):
            t = tokens[j]

            # Skip another address or size token
            if t.startswith("0x") and HEXADDR_RE.fullmatch(t):
                continue

            # Skip purely numeric sizes
            if t.isdigit():
                continue

            # Skip object files / archives
            if t.endswith((".o", ".obj", ".a", ".so")):
                continue

            # Skip map keywords
            if t in ("load", "LOAD", "section", "SECTION", "of"):
                continue

            # Clean some punctuation
            t_clean = t.strip()

            if is_plausible_symbol_name(t_clean):
                cand = t_clean
                break

        if cand is None:
            continue

        syms.append(Sym(addr=addr, name=cand))

    # Deduplicate by (addr,name), sort by addr
    syms = sorted(set(syms), key=lambda s: (s.addr, s.name))

    # If there are multiple names at same addr, keep them all; resolver will pick last <= addr.
    return syms


def resolve_addr(addr: int, syms: List[Sym]) -> Optional[Tuple[Sym, int]]:
    """
    Find symbol with greatest sym.addr <= addr.
    Returns (sym, offset) or None.
    """
    if not syms:
        return None
    addrs = [s.addr for s in syms]
    i = bisect_right(addrs, addr) - 1
    if i < 0:
        return None
    sym = syms[i]
    return sym, addr - sym.addr


def main():
    ap = argparse.ArgumentParser(
        description="Resolve stack return addresses (pc=...) against GNU ld .map symbols."
    )
    ap.add_argument("--map", required=True, help="Path to .map file")
    ap.add_argument("--dump", required=False, help="Path to exception/stack dump text (default: stdin)")
    ap.add_argument(
        "--use",
        choices=("pc", "ra"),
        default="pc",
        help="Which field to resolve: pc (default) or ra"
    )
    ap.add_argument(
        "--max-offset",
        type=lambda x: int(x, 0),
        default=0x20000,
        help="Max allowed offset from symbol (default: 0x20000) to consider as match"
    )
    ap.add_argument(
        "--show-raw",
        action="store_true",
        help="Also show raw line if desired"
    )
    args = ap.parse_args()

    with open(args.map, "r", errors="replace") as f:
        map_text = f.read()

    syms = parse_map_symbols(map_text)
    if not syms:
        print("ERROR: no symbols parsed from map file. (Map format unexpected?)", file=sys.stderr)
        sys.exit(2)

    if args.dump:
        with open(args.dump, "r", errors="replace") as f:
            dump_text = f.read()
    else:
        dump_text = sys.stdin.read()

    entries = parse_stack_dump(dump_text)
    if not entries:
        print("ERROR: no stack RA lines matched. Expected lines like: [SP+0x0014] RA=0x... (pc=0x...)", file=sys.stderr)
        sys.exit(3)

    # Output
    print("SP_off  addr_used        symbol+off")
    print("------  ---------------  ----------------------------------------")

    for spoff, ra, pc in entries:
        addr = pc if args.use == "pc" else ra
        res = resolve_addr(addr, syms)
        if res is None:
            print(f"0x{spoff:04X}  0x{addr:08X}       <no symbol>")
            continue
        sym, off = res
        if off > args.max_offset:
            print(f"0x{spoff:04X}  0x{addr:08X}       <far from symbol> {sym.name}+0x{off:X} @0x{sym.addr:08X}")
            continue
        print(f"0x{spoff:04X}  0x{addr:08X}       {sym.name}+0x{off:X}  (sym@0x{sym.addr:08X})")

    # Optional: show count
    print(f"\nResolved {len(entries)} addresses using {len(syms)} map symbols.")


if __name__ == "__main__":
    main()

