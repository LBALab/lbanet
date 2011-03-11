#!/bin/sh
cd ../../Patch/Lbanet
icepatch2calc .
icepatch2server --IcePatch2.Endpoints="tcp -p 10000" . &
