#!/bin/sh
svn export --force Data/ Patch/Lbanet/Data/
rm -rf Servers/IceGridServer/Data
mv Data/ Servers/IceGridServer
cp *.HQR Servers/IceGridServer/Data/Worlds/Lba1Original/Models 
