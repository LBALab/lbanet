#!/bin/sh
rm ./cpp/*.cpp
rm ./include/*.h
cd ./slice
slice2cpp -I. ./*.ice --output-dir ../cpp
mv ../cpp/*.h ../include/
cd ..
