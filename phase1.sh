#!/bin/bash
gcc sample.c -o output -lfcgi
kill -9 `pidof output`
spawn-fcgi -a 127.0.0.1 -p 2016 output