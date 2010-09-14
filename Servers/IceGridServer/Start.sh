#!/bin/sh
rm -rf db/node/*
rm -rf db/registry/*
icegridnode --Ice.Config=config.grid &
sleep 5
icegridadmin --Ice.Config=config.grid -e "application add 'application.xml'"
icegridadmin --Ice.Config=config.grid -e "server start LBANetGlacier2"
icegridadmin --Ice.Config=config.grid -e "server start PollingChatServer-1"
