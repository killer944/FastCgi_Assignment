# TARGET = output
# CC = gcc
# INCLUDE = memcache.h seperater.h connect.h
# CFLAGS = -Wall -I.
# LDFLAGS = -lfcgi -lmysqlclient -lmemcached -lpthread -lconfig
# SOURCES = phase4.c
# OBJECTS = output
# all: $(TARGET)
# $(TARGET): $(OBJECTS)
# 	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJECTS) $(LDFLAGS) $(shell mysql_config --cflags) $(shell mysql_config --libs)
# clean:
# 	rm -f $(TARGET) $(OBJECTS)
# run: $(TARGET)
# 	pid=$(shell pidof $(TARGET)) && kill -9 $$pid || true
#     spawn-fcgi -a 127.0.0.1 -p 2016 $(TARGET)
CC = gcc
SRC = src;
OBJ =obj;
TARGET = PHASE1
INCLUDE = -I include

MYSQL_CONFIG= $$(mysql_config --cflags --libs)
spawn:compile
	spawn-fcgi -a 127.0.0.1 -p 2016 -n obj/output
compile:
	gcc $(INCLUDE) src/main.c -o obj/output -lpthread -lmemcached -lfcgi -lconfig -lodbc $(MYSQL_CONFIG) 