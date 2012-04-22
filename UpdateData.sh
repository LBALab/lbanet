#!/bin/sh

echo Updating Data directory...
svn update Data
svn export --force Data/ Patch/Lbanet/Data/
cp -rf Data Servers/IceGridServer
cp *.HQR Servers/IceGridServer/Data/Worlds/Lba1Original/Models 


echo Updating Colozen directory...
svn update tmpsvn/Colozen
svn export --force tmpsvn/Colozen Patch/Lbanet/Data/Worlds/Colozen
cp -rf tmpsvn/Colozen Servers/IceGridServer/Data/Worlds


echo Updating Lba1Expanded directory...
svn update tmpsvn/Lba1Expanded
svn export --force tmpsvn/Lba1Expanded Patch/Lbanet/Data/Worlds/Lba1Expanded
cp -rf tmpsvn/Lba1Expanded Servers/IceGridServer/Data/Worlds


echo Updating Lba1Original directory...
svn update tmpsvn/Lba1Original
svn export --force tmpsvn/Lba1Original Patch/Lbanet/Data/Worlds/Lba1Original
cp -rf tmpsvn/Lba1Original Servers/IceGridServer/Data/Worlds


echo Updating Lba2Original directory...
svn update tmpsvn/Lba2Original
svn export --force tmpsvn/Lba2Original Patch/Lbanet/Data/Worlds/Lba2Original
cp -rf tmpsvn/Lba1ExpLba2Original Servers/IceGridServer/Data/Worlds

