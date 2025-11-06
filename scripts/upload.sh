#!/bin/bash

set -e

if [[ -z ${SWITCH_HOSTNAME} ]]; then
    echo "Env var SWITCH_HOSTNAME must be set."
    exit 1
fi

APP_TITLE="NX-ScreenUploader"
APP_TITLE_ID="420000000001BF52"

pushd build
ftp -inv ${SWITCH_HOSTNAME} 5000 << EOF
cd /atmosphere/contents/${APP_TITLE_ID}
delete exefs.nsp
put ${APP_TITLE}.nsp
rename ${APP_TITLE}.nsp exefs.nsp
EOF
popd
