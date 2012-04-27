#!/bin/sh
icegridadmin --Ice.Config=config.grid -e "server start LBANetGlacier2"
icegridadmin --Ice.Config=config.grid -e "server start PollingChatServer-1"
icegridadmin --Ice.Config=config.grid -e "server start WorldServer-Lba1Original"
icegridadmin --Ice.Config=config.grid -e "server start WorldServer-Lba2Original"
icegridadmin --Ice.Config=config.grid -e "server start WorldServer-Lba1Expanded"
icegridadmin --Ice.Config=config.grid -e "server start WorldServer-Colozen"

icegridadmin --Ice.Config=config.grid -e "server start Lba1OriginalPatch"
icegridadmin --Ice.Config=config.grid -e "server start Lba2OriginalPatch"
icegridadmin --Ice.Config=config.grid -e "server start Lba1ExpandedPatch"
icegridadmin --Ice.Config=config.grid -e "server start ColozenPatch"

