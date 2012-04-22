#!/bin/sh
svn export --force Data/ Patch/Lbanet/Data/
mv -f Data Servers/IceGridServer/Data
cp *.HQR Servers/IceGridServer/Data/Worlds/Lba1Original/Models 

cd tmpsvn

rm -rf Colozen
mkdir Colozen
svn checkout http://colozen.googlecode.com/svn/trunk/ Colozen
svn export --force Colozen Patch/Lbanet/Data/Colozen
mv -f Colozen Servers/IceGridServer/Data/Colozen

rm -rf Lba1Expanded
mkdir Lba1Expanded
svn checkout http://lbaexpanded.googlecode.com/svn/trunk/ Lba1Expanded
svn export --force Lba1Expanded Patch/Lbanet/Data/Lba1Expanded
mv -f Lba1Expanded Servers/IceGridServer/Data/Lba1Expanded

rm -rf Lba1Original
mkdir Lba1Original
svn checkout http://lbanet-orig-worlds.googlecode.com/svn/trunk/Lba1Original Lba1Original
svn export --force Lba1Original Patch/Lbanet/Data/Lba1Original
mv -f Lba1Original Servers/IceGridServer/Data/Lba1Original

rm -rf Lba2Original
mkdir Lba2Original
svn checkout http://lbanet-orig-worlds.googlecode.com/svn/trunk/Lba2Original Lba2Original
svn export --force Lba2Original Patch/Lbanet/Data/Lba2Original
mv -f Lba1ExpLba2Originalnded Servers/IceGridServer/Data/Lba2Original

cd ..
