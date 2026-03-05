#!/bin/bash
#Export artefact to local DEV FTP Server

# $1 : deploy folder
# $2 : script folder
# $3 : FTP Server

echo "Copy script 'upload_ftp_server.sh' to deploy folder $1"

cp $2/upload_ftp_server.sh $1
cp $2/start_local_ftp_server.sh $1

# set FTP Server as defined in project
FTP_BASE="ftp://$3"
sed -i "s|^FTP_BASE=.*|FTP_BASE=${FTP_BASE}|" $1/upload_ftp_server.sh
echo "Set FTP to $3"

