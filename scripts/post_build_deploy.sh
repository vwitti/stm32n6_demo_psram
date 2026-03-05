#!/bin/bash
#Export artefact to local deploy folder

### include helper scripts ###
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source ${SCRIPT_DIR}/helper_functions.sh

### passed parameter ###
# $1 : Deploy Folder
# $2 : Artefact Name
# $3 : Progtype FSBL or APPLI
# $4 : file with list of update artefacts
echo "Deploy binaries $2 to folder $1"

UPLOAD_LIST="$1/$4"

### Update Artefact content file ###
if [ "$3" = "FSBL" ]; then							### Update keys for FSBL ###
### Copy Artefacts ###
	cp -f $2.trusted.flash.bin $1/$2.trusted.flash.bin
	cp -f $2.trusted.header $1/$2.trusted.header
	set_key_value_pair $UPLOAD_LIST FSBL_BIN $2.trusted.flash.bin
	set_key_value_pair $UPLOAD_LIST FSBL_HEADER $2.trusted.header  
elif [ "$3" = "APPLI" ]; then						### Update keys for APPLI ###
### Copy Artefacts ###
	cp -f $2.trusted.bin $1/$2.trusted.bin
	cp -f $2.trusted.header $1/$2.trusted.header
	set_key_value_pair $UPLOAD_LIST APPLI_BIN $2.trusted.bin
	set_key_value_pair $UPLOAD_LIST APPLI_HEADER $2.trusted.header
else
	echo "Unsupported program type"
	exit 1
fi
