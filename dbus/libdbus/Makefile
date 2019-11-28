#CC = gcc

LIB_INC=$(shell pkg-config --cflags dbus-1)
CFLAGS+=$(LIB_INC)
CFLAGS+=-g -Wall
LIB = $(shell pkg-config --libs dbus-1)
LIBS+=$(LIB)

.PHONY : all
all : dbus-server dbus-client recv-signal

dbus-server : dbus-server.c common.c
	gcc -o $@ $(CFLAGS) $(LIBS) $^


dbus-client : dbus-client.c common.c
	gcc -o $@ $(CFLAGS) $(LIBS) $^


recv-signal : recv-signal.c common.c
	gcc -o $@ $(CFLAGS) $(LIBS) $^


 .PHONY : clean
clean :
	rm dbus-server dbus-client recv-signal
