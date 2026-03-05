#!/bin/bash
# Analyse Stack Usage

#echo "Relativ path to script director in $1"
#echo "Toolchain path in $2"
#echo "Generating Stackusage for project $3"

FILE="/usr/bin/arm-none-eabi-objdump"

if [ ! -f "$FILE" ]; then
    echo "Either tool is not found in /usr/bin or it is not installed"
    echo "you may run 'sudo apt install binutils-arm-none-eabi' or similar"
    echo "depending on your dist"
    exit 1 
fi

python $1/stack_analyzer_pyelf.py --elf $3.elf  --path . --top 15
