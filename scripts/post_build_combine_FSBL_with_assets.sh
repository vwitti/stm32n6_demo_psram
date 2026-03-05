#!/usr/bin/env bash
set -euo pipefail

# (c) Chad 2026

usage() {
  cat <<EOF
Usage:
  $(basename "$0") <file1.bin> <file2.bin> <out.bin> <offset_header.h>

Behavior:
  - Reads OFFSET_ADDR from header file (#define OFFSET_ADDR 0x....)
  - Writes file1 at offset 0
  - Writes file2 at OFFSET_ADDR
  - Pads with 0x00 between file1 end and OFFSET_ADDR if needed
  - Fails if file1 is larger than OFFSET_ADDR
  - Fails if output file would exceed 1MB
EOF
}

if [[ $# -ne 4 ]]; then
  usage >&2
  exit 2
fi

F1="$1"
F2="$2"
OUT="$3"
HDR="$4"

[[ -f "$F1" ]] || { echo "Error: file not found: $F1" >&2; exit 1; }
[[ -f "$F2" ]] || { echo "Error: file not found: $F2" >&2; exit 1; }
[[ -f "$HDR" ]] || { echo "Error: header not found: $HDR" >&2; exit 1; }

# Extract: e.g. #define XSPI_OFFSET_FSBL_ASSETS 0x80000
OFFSET_HEX=$(awk '$1=="#define" && $2=="XSPI_OFFSET_FSBL_ASSETS" {print $3}' "$HDR")

if [[ -z "${OFFSET_HEX:-}" ]]; then
  echo "Error: OFFSET_ADDR not found in header: $HDR" >&2
  exit 1
fi

OFFSET_DEC=$((OFFSET_HEX))

SIZE1=$(stat -c%s "$F1")
SIZE2=$(stat -c%s "$F2")

if (( SIZE1 > OFFSET_DEC )); then
  printf 'Error: first file is too large (%d bytes / 0x%X), must be <= %s\n' \
    "$SIZE1" "$SIZE1" "$OFFSET_HEX" >&2
  printf '       Increase XSPI_OFFSET_FSBL_ASSETS in tcsglobal/system_constants.h to a value >= 0x%X\n' "$SIZE1" >&2
  exit 1
fi

TOTAL_SIZE=$(( OFFSET_DEC + SIZE2 ))
MAX_SIZE=$(( 1024 * 1024 ))  # 1MB

if (( TOTAL_SIZE > MAX_SIZE )); then
  printf 'Error: output would exceed 1MB (need %d bytes / 0x%X, max %d bytes)\n' "$TOTAL_SIZE" "$TOTAL_SIZE" "$MAX_SIZE" >&2
  printf 'This is a limitation of the STM32N6 bootcode and ExtMem Manager\n' >&2
  exit 1
fi

# Create/truncate output
: > "$OUT"

# Write file1 at offset 0
cat "$F1" >> "$OUT"

# Pad up to OFFSET if needed
PAD=$(( OFFSET_DEC - SIZE1 ))
if (( PAD > 0 )); then
  dd if=/dev/zero bs=1 count="$PAD" status=none >> "$OUT"
fi

# Write file2 at OFFSET
cat "$F2" >> "$OUT"

printf 'OK: wrote %s\n' "$OUT"
printf '  file1: %s (%d bytes)\n' "$F1" "$SIZE1"
printf '  file2: %s (%d bytes) @ offset %s\n' "$F2" "$SIZE2" "$OFFSET_HEX"
printf '  total: %d bytes\n' "$(stat -c%s "$OUT")"
