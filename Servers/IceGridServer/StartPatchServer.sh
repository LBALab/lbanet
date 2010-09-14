#!/bin/sh
cd ../../patch_server/release
icepatch2calc .
icepatch2server --IcePatch2.Endpoints="tcp -p 10000" . &
