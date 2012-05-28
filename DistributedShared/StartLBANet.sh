echo Patching game, this might take several minutes..
icepatch2client --IcePatch2.Remove=0 --IcePatch2.Endpoints="tcp -h 88.191.144.87 -p 10000" . | tee patching.log
echo Starting game...
./LBANetGame

