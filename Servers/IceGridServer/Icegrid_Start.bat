SET UtilPath=%~dp0
call Icegrid_CleanUp.bat
call %ICE_HOME%\bin\icegridnode --Ice.Config=config.grid

