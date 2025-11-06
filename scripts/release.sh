#!/usr/bin/env bash

set -e

APP_TITLE="NX-ScreenUploader"
APP_TITLE_ID="420000000001BF52"

rm -rf release
mkdir release
cd release
mkdir -p config/${APP_TITLE}
mkdir -p atmosphere/contents/${APP_TITLE_ID}/flags
cp ../../config.ini config/${APP_TITLE}/config.ini
cp ../../toolbox.json atmosphere/contents/${APP_TITLE_ID}/toolbox.json
cp ../../build/NX-ScreenUploader.nsp atmosphere/contents/${APP_TITLE_ID}/exefs.nsp
touch atmosphere/contents/${APP_TITLE_ID}/flags/boot2.flag
zip -r ${APP_TITLE} ./*
