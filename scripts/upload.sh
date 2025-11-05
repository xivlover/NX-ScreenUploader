#!/usr/bin/env bash

if [[ -z ${SWITCH_HOSTNAME} ]]; then
    echo "Env var SWITCH_HOSTNAME must be set."
    exit 1
fi

cd build
ftp -inv ${SWITCH_HOSTNAME} 5000 << EOF
cd /atmosphere/contents/420000000001BF52
delete exefs.nsp
put screen-uploader.nsp
rename screen-uploader.nsp exefs.nsp
EOF
