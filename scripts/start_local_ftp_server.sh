#!/bin/bash
#Start local FTP Server for update

set -e

python -m pyftpdlib --username=Stm32N6User --password=Stm32N6Pass --port=2121

