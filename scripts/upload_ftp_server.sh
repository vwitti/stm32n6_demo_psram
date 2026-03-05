#!/bin/bash
#Export artefact to external FTP Server with curl. This is only neccessary if you do not work local. 
#For local work just run script "start_local_ftp_server.sh"

set -e

# Usage
if [[ $# -ne 1 ]]; then
    echo "Usage: $0 {all|FSBL|APPLI|TCS_ROMFS|TOUCHGFX}"
    exit 1
fi

TARGET="$1"

# FTP server address is set by deploy script
FTP_BASE="n.n."   
echo "Export deploy folder to ftp server $FTP_BASE"

#####   upload file    #####
############################
# $1 : file to upload
upload_to_ftp()
{
	file=$1

    # Optional: check file exists
    if [ ! -f "$file" ]; then
        echo "Skipping, file not found: $file"
        return
    fi
	
	# Only filename on server:
	remote="$FTP_BASE/$(basename "$file")"
	
	echo "Uploading: $file -> $remote"
	curl -sT "$file" "$remote"
}


#####    Export FSBL   #####
############################
export_to_ftp_fsbl() 
{
	file=$(grep "FSBL_BIN" update_list.txt | cut -d= -f2)
	upload_to_ftp $file
	file=$(grep "FSBL_HEADER" update_list.txt | cut -d= -f2)
	upload_to_ftp $file
}

#####   Export APPLI   #####
############################
export_to_ftp_appli() 
{
	file=$(grep "APPLI_BIN" update_list.txt | cut -d= -f2)
	upload_to_ftp $file
	file=$(grep "APPLI_HEADER" update_list.txt | cut -d= -f2)
	upload_to_ftp $file
}

##### Export TCO_ROMFS #####
############################
export_to_ftp_tco_romfs() 
{
	file=$(grep "TCS_ROMFS_BIN" update_list.txt | cut -d= -f2)
	upload_to_ftp $file
	file=$(grep "TCS_ROMFS_HEADER" update_list.txt | cut -d= -f2)
	upload_to_ftp $file
}

##### Export TCO_ROMFS #####
############################
export_to_ftp_touchgfx_assets_image() 
{
	file=$(grep "TOUCHGFX_ASSETS_BIN" update_list.txt | cut -d= -f2)
	upload_to_ftp $file
	file=$(grep "TOUCHGFX_ASSETS_CRC" update_list.txt | cut -d= -f2)
	upload_to_ftp $file
}

##### Export UpdateList #####
#############################
export_to_ftp_update_list() 
{
	upload_to_ftp update_list.txt
}

case "$TARGET" in
    all)
        echo "Export all files to ${FTP_BASE}"
        export_to_ftp_fsbl
        export_to_ftp_appli
        export_to_ftp_tco_romfs
        export_to_ftp_update_list
        export_to_ftp_touchgfx_assets_image
        ;;
    FSBL)
    	echo "Export FSBL files to ${FTP_BASE}"
        export_to_ftp_fsbl
        export_to_ftp_update_list
        ;;
    APPLI)
        echo "Export APPLI files to ${FTP_BASE}"
        export_to_ftp_appli
        export_to_ftp_update_list
        ;;
    TCS_ROMFS)
        echo "Export TCS_ROMFS files to ${FTP_BASE}"
        export_to_ftp_tco_romfs
        export_to_ftp_update_list
        ;;
    TOUCHGFX)
        echo "Export TOUCHGFX files to ${FTP_BASE}"
        export_to_ftp_touchgfx_assets_image
        export_to_ftp_update_list
        ;;
    *)
        echo "ERROR: Invalid parameter: '$TARGET'"
        echo "Valid options are: all, FSBL, APPLI, TCS_ROMFS, TOUCHGFX"
        exit 1
        ;;
esac

echo "Done."
