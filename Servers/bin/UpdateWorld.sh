#!/bin/sh


case "$1" in
'Colozen')
svn update ~/neolbanet/tmpsvn/Colozen
svn export --force ~/neolbanet/tmpsvn/Colozen ~/neolbanet/Servers/IceGridServer/Data/Worlds/Colozen
icepatch2calc ~/neolbanet/Servers/IceGridServer/Data/Worlds/Colozen
;;

'Lba1Expanded')
svn update ~/neolbanet/tmpsvn/Lba1Expanded
svn export --force ~/neolbanet/tmpsvn/Lba1Expanded ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Expanded
icepatch2calc ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Expanded
;;

'Lba1Original')
svn update ~/neolbanet/tmpsvn/Lba1Original
svn export --force ~/neolbanet/tmpsvn/Lba1Original ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Original
icepatch2calc ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba1Original
;;

'Lba2Original')
svn update ~/neolbanet/tmpsvn/Lba2Original
svn export --force ~/neolbanet/tmpsvn/Lba2Original ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba2Original
icepatch2calc ~/neolbanet/Servers/IceGridServer/Data/Worlds/Lba2Original
;;
esac