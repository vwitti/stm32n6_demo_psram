#!/bin/bash
#Export Update tcs_romfs image

### include helper scripts ###
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source ${SCRIPT_DIR}/helper_functions.sh

# $1 : Deploy Folder
# $2 : Folder with tcs_romfs image files (source)
# $3 : file with list of update artefacts
echo "Update TCS ROM Image $2 in deploy folder $1"

UPLOAD_LIST="$1/$3"

# Copy files from tcs/romfs/TCO_ROMFS_FILES to image
$2/copyfiles_tcs_romfs.sh $2

# Export to deploy folder
cp -f tcs_romfs.truncated.bin $1
cp -f tcsromfs.crc $1

# Update artefact file
set_key_value_pair $UPLOAD_LIST TCS_ROMFS_BIN tcs_romfs.truncated.bin
set_key_value_pair $UPLOAD_LIST TCS_ROMFS_HEADER tcsromfs.crc
