#!/bin/sh

svn export --force Data/ Patch/Lbanet/Data/
mv -f Data Servers/IceGridServer
cp *.HQR Servers/IceGridServer/Data/Worlds/Lba1Original/Models 

cd tmpsvn

svn update Colozen
svn export --force Colozen ../Patch/Lbanet/Data/Worlds/Colozen
cp -rf Colozen ../Servers/IceGridServer/Data/Worlds/Colozen


svn update Lba1Expanded
svn export --force Lba1Expanded ../Patch/Lbanet/Data/Worlds/Lba1Expanded
cp -rf Lba1Expanded ../Servers/IceGridServer/Data/Worlds/Lba1Expanded

svn update Lba1Original
svn export --force Lba1Original ../Patch/Lbanet/Data/Worlds/Lba1Original
cp -rf Lba1Original ../Servers/IceGridServer/Data/Worlds/Lba1Original

svn update Lba2Original
svn export --force Lba2Original ../Patch/Lbanet/Data/Worlds/Lba2Original
cp -rf Lba1ExpLba2Originalnded ../Servers/IceGridServer/Data/Worlds/Lba2Original

cd ..
