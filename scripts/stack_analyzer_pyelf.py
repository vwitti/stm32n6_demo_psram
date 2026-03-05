#!/usr/bin/env python3
"""
stack_analyzer_auto.py
----------------------
Automatische Analyse der Stacknutzung auf Basis von GCC .su-Dateien + ELF Callgraph.
Benötigt: arm-none-eabi-objdump im PATH
"""

import os
import subprocess
import re
import argparse
from collections import defaultdict
from functools import lru_cache

# ------------------------------------------------------
# Argumente
# ------------------------------------------------------
parser = argparse.ArgumentParser(description="Analysiert kumulative Stacktiefe aus ELF und .su-Dateien")
parser.add_argument("--elf", required=True, help="Pfad zur ELF-Datei (z.B. build/project.elf)")
parser.add_argument("--path", default=".", help="Pfad zu .su-Dateien")
parser.add_argument("--top", type=int, default=10, help="Top N Funktionen anzeigen")
parser.add_argument("--dot", action="store_true", help="Graphviz .dot-Datei ausgeben")
args = parser.parse_args()

# Ensure that tool is somewhere in the path
path_to_gcc_objdump="arm-none-eabi-objdump"
    
# ------------------------------------------------------
# Schritt 1: .su-Dateien einlesen
# ------------------------------------------------------
stack_usage = {}
for root, _, files in os.walk(args.path):
    for fname in files:
        if fname.endswith(".su"):
            with open(os.path.join(root, fname)) as f:
                for line in f:
                    parts = line.strip().split("\t")
                    #Linux /repos/git/ASG-EVO/ASG-EVO/N6570-DK_BASIS/FSBL/Src/main.c:66:5:main	24	static
                    #Window C:/repos/git/ASG-EVO/ASG-EVO/N6570-DK_BASIS/FSBL/Src/main.c:66:5:main	24	static
                    func = parts[0].split(":")[-1] # Get string behind last :
                    stack_bytes = int(parts[1])
                    stack_usage[func] = stack_bytes
                    ################################################################
                    #Format of *.su seems diffrent to knowledge of Chad
                    #parts = line.strip().split(":")
                    #if len(parts) >= 5:
                    #    func = parts[3]
                    #    try:
                    #        stack_bytes = int(parts[4])
                    #    except ValueError:
                    #        stack_bytes = 0
                    #    stack_usage[func] = stack_bytes

if not stack_usage:
    print("!! Keine .su-Dateien gefunden – bitte mit -fstack-usage kompilieren!")
    exit(1)

#print(f"{len(stack_usage)} Funktionen mit Stackinformationen gefunden.")

# ------------------------------------------------------
# Schritt 2: Callgraph aus ELF-Datei generieren
# ------------------------------------------------------
#print("Analysiere Callgraph aus ELF-Datei...")

calls = defaultdict(list)
try:
    # disassemble ELF mit Funktionssymbolen
    result = subprocess.run([path_to_gcc_objdump, "-d", "--demangle", args.elf],
                            capture_output=True, text=True, check=True)
    current_func = None
    for line in result.stdout.splitlines():
        # Funktionsdefinition erkennen
        m_func = re.match(r"^([0-9a-fA-F]+) <(.+)>:$", line)
        if m_func:
            current_func = m_func.group(2)
            continue
        # Call-Befehl erkennen
        m_call = re.search(r"bl\s+([0-9a-fA-F]+) <(.+)>", line)
        if m_call and current_func:
            callee = m_call.group(2)
            if callee != current_func:
                calls[current_func].append(callee)
except subprocess.CalledProcessError as e:
    print("ERR: Fehler beim Ausführen von objdump:", e)
    exit(1)

#print(f"OK {len(calls)} Funktionen mit Aufrufbeziehungen gefunden.\n")

# ------------------------------------------------------
# Schritt 3: Kumulative Stackberechnung
# ------------------------------------------------------
@lru_cache(maxsize=None)
def cumulative_stack(func):
    local = stack_usage.get(func, 0)
    if func not in calls or not calls[func]:
        return local
    return local + max((cumulative_stack(c) for c in calls[func]), default=0)

cumulative = {f: cumulative_stack(f) for f in stack_usage.keys()}
sorted_funcs = sorted(cumulative.items(), key=lambda x: x[1], reverse=True)

# ------------------------------------------------------
# Schritt 4: Ergebnisse ausgeben
# ------------------------------------------------------
if 0:
    print(f"Top {args.top} Funktionen mit hoechstem kumulativem Stackverbrauch:\n")
    print(f"{'Funktion':40s} {'Lokal':>10s} {'Kumulativ':>12s}")
    print("-" * 64)
    for func, total in sorted_funcs[:args.top]:
        print(f"{func:40s} {stack_usage.get(func,0):10d} {total:12d}")

    max_func, max_val = sorted_funcs[0]
    print(f"\nMaximale kumulative Stacktiefe: {max_val} Bytes (bei {max_func})")

print(f"\nStack Usage Thread Funktionen mit 'ThreadASG_', see wiki for more details:")
print(f"{'Funktion':40s} {'Lokal':>10s} {'Kumulativ':>12s}")
print("-" * 64)

#for entry in sorted_funcs:
for func, total in sorted_funcs[:len(sorted_funcs)]:
    func_parts = func.strip().split("_")
    if func_parts[0] == "ThreadASG":
        print(f"{func:40s} {stack_usage.get(func,0):10d} {total:12d}")
        
print("-" * 64)

# ------------------------------------------------------
# Schritt 5 (optional): DOT-Datei ausgeben
# ------------------------------------------------------
if args.dot:
    dotfile = "stack_graph.dot"
    with open(dotfile, "w") as f:
        f.write("digraph StackGraph {\n")
        for caller, callees in calls.items():
            for callee in callees:
                f.write(f"  \"{caller}\" -> \"{callee}\";\n")
        f.write("}\n")
    print(f"\nCallgraph gespeichert als {dotfile} (mit Graphviz visualisierbar)")
