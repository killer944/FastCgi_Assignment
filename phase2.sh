#!/bin/bash
gcc phase2.c $(mysql_config --libs) -o output $(mysql_config --cflags) -lfcgi
kill -9 `pidof output`
spawn-fcgi -a 127.0.0.1 -p 2016 output
