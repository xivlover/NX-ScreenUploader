#!/usr/bin/env bash

set -e

rm -rf release
mkdir release
cd release
mkdir -p config/sys-screen-uploader
mkdir -p atmosphere/contents/420000000001BF52/flags
cp ../../config.ini config/sys-screen-uploader/config.ini
cp ../../toolbox.json atmosphere/contents/420000000001BF52/toolbox.json
cp ../../build/screen-uploader.nsp atmosphere/contents/420000000001BF52/exefs.nsp
touch atmosphere/contents/420000000001BF52/flags/boot2.flag
zip -r sys-screen-uploader ./*
