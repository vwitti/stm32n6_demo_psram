#!/bin/bash
#Sign binary file with trusted header
#echo "Relativ path to script director in $1"
#echo "Toolchain path in $2"
#echo "Signing executable binary $3"
echo "Use -dump option to show generated trusted header"

#run the signing tool
#$2/STM32_SigningTool_CLI -s -bin $3.bin -nk -of 0x80000000 -t fsbl -o $3.trusted.bin -hv 2.3 -align -dump $3.trusted.bin
$2/STM32_SigningTool_CLI -s -bin $3.bin -nk -of 0x80000000 -t fsbl -o $3.trusted.bin -hv 2.3 -align

# Set write flag
chmod +w $3.trusted.bin

# Write trusted header into separate file, faster and easiert to check
dd if=$3.trusted.bin of=$3.trusted.header bs=1 count=1024 status=none
