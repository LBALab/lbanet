#!/bin/sh

echo Updating Data directory...
svn update ~/neolbanet/Data
svn export --force ~/neolbanet/Data/ ~/neolbanet/Patch/Lbanet/Data/
cp -rf ~/neolbanet/Data ~/neolbanet/Servers/IceGridServer

cp ~/neolbanet/*.HQR ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Original/Models 


echo Updating Colozen directory...
svn update ~/neolbanet/tmpsvn/Colozen
svn export --force ~/neolbanet/tmpsvn/Colozen ~/neolbanet/Patch/Lbanet/Data/Worlds/Colozen
cp -rf ~/neolbanet/tmpsvn/Colozen ~/neolbanet/Servers/IceGridServer/Data/Worlds


echo Updating Lba1Expanded directory...
svn update ~/neolbanet/tmpsvn/Lba1Expanded
svn export --force ~/neolbanet/tmpsvn/Lba1Expanded ~/neolbanet/Patch/Lbanet/Data/Worlds/Lba1Expanded
cp -rf ~/neolbanet/tmpsvn/Lba1Expanded ~/neolbanet/Servers/IceGridServer/Data/Worlds


echo Updating Lba1Original directory...
svn update ~/neolbanet/tmpsvn/Lba1Original
svn export --force ~/neolbanet/tmpsvn/Lba1Original ~/neolbanet/Patch/Lbanet/Data/Worlds/Lba1Original
cp -rf ~/neolbanet/tmpsvn/Lba1Original ~/neolbanet/Servers/IceGridServer/Data/Worlds


echo Updating Lba2Original directory...
svn update ~/neolbanet/tmpsvn/Lba2Original
svn export --force ~/neolbanet/tmpsvn/Lba2Original ~/neolbanet/Patch/Lbanet/Data/Worlds/Lba2Original
cp -rf ~/neolbanet/tmpsvn/Lba2Original ~/neolbanet/Servers/IceGridServer/Data/Worlds
