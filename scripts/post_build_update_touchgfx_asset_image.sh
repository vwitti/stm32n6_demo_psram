#!/bin/bash
#Export Update touchgfx assets rom image

if ! command -v crc32 >/dev/null 2>&1; then
    echo "crc32 ist NICHT installiert!"
    echo "Installieren mit: sudo apt install libarchive-zip-perl"
fi

### include helper scripts ###
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source ${SCRIPT_DIR}/helper_functions.sh

# $1 : Deploy Folder
# $2 : Artefact Name
# $3 : Folder with tcs_romfs image files (source)
# $4 : file with list of update artefacts
#echo "$1 : Deploy Folder"
#echo "$2 : Artefact Name"
#echo "$3 : Folder with tcs_romfs image files (source)"
#echo "$4 : file with list of update artefacts"
echo "Update TouchGFX asset ROM Image $2.touchgfx_assets.bin in deploy folder $1"

WORK_IMG_FLASH_CRC="touchgfx.crc"			# We install this into the TCS_ROMFS FAT16 filesystem, se keep old 8.3 style

TOUCHGX_ASSETS_CRC32=$(crc32 $2.touchgfx_assets.bin)
rm -f ${WORK_IMG_FLASH_CRC}
echo "${TOUCHGX_ASSETS_CRC32}" >> ${WORK_IMG_FLASH_CRC}
#echo "TOUCHGFX CRC32 : ${TOUCHGX_ASSETS_CRC32}"

### copy CRC file to TCS romfs image only copy only ###
### if diffrent or not existing                     ###
if [[ -f "$3/TCS_ROMFS_FILES/${WORK_IMG_FLASH_CRC}" ]]; then
	# Remote file in TCS ROMFS exists, check if there is a diff and update
	if ! diff -q ${WORK_IMG_FLASH_CRC} $3/TCS_ROMFS_FILES/${WORK_IMG_FLASH_CRC} > /dev/null; then
		cp ${WORK_IMG_FLASH_CRC} $3/TCS_ROMFS_FILES	
	fi
else
	# Not existing, simply copy
	cp ${WORK_IMG_FLASH_CRC} $3/TCS_ROMFS_FILES  
fi

# Export to deploy folder
cp -f $2.touchgfx_assets.bin $1
cp -f ${WORK_IMG_FLASH_CRC} $1

# Update artefact file
UPLOAD_LIST="$1/$4"
set_key_value_pair $UPLOAD_LIST TOUCHGFX_ASSETS_BIN $2.touchgfx_assets.bin
set_key_value_pair $UPLOAD_LIST TOUCHGFX_ASSETS_CRC ${WORK_IMG_FLASH_CRC}
