#!/bin/sh
rm -rf db/node/*
rm -rf db/registry/*
icegridnode --Ice.Config=config.grid &



