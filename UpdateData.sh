#!/bin/sh

echo Updating Data directory...
svn update ~/neolbanet/Data
svn export --force ~/neolbanet/Data/ ~/neolbanet/Patch/Lbanet/Data/
svn export --force ~/neolbanet/Data/ ~/neolbanet/Servers/IceGridServer/Data

echo Updating Colozen directory...
svn update ~/neolbanet/tmpsvn/Colozen
svn export --force ~/neolbanet/tmpsvn/Colozen ~/neolbanet/Servers/IceGridServer/Data/Worlds/Colozen
icepatch2calc ~/neolbanet/Servers/IceGridServer/Data/Worlds/Colozen


echo Updating Lba1Expanded directory...
svn update ~/neolbanet/tmpsvn/Lba1Expanded
svn export --force ~/neolbanet/tmpsvn/Lba1Expanded ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Expanded
icepatch2calc ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Expanded


echo Updating Lba1Original directory...
svn update ~/neolbanet/tmpsvn/Lba1Original
svn export --force ~/neolbanet/tmpsvn/Lba1Original ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Original
icepatch2calc ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Original


echo Updating Lba2Original directory...
svn update ~/neolbanet/tmpsvn/Lba2Original
svn export --force ~/neolbanet/tmpsvn/Lba2Original ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba2Original
icepatch2calc ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba2Original

cp ~/neolbanet/*.HQR ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Original/Models 
