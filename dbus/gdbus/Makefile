all : gdbus_server gdbus_client 
.PHONY : all

#CC = gcc

LIB_INC=$(shell pkg-config --cflags glib-2.0 gio-unix-2.0)
CFLAGS+=$(LIB_INC)
CFLAGS+=-g -Wall
LIB = $(shell pkg-config --libs glib-2.0 gio-unix-2.0)
LIBS+=$(LIB)


#GDBUS_SERVER_SRC =  gdbus_server.c
#GDBUS_CLIENT_SRC =  gdbus_client.c

gdbus_server : gdbus_server.c Building.c 
	gcc -o $@ $(CFLAGS) $(LIBS) $^


gdbus_client : gdbus_client.c Building.c
	gcc -o $@ $(CFLAGS) $(LIBS) $^


Building.c Building.h : Building.xml
	gdbus-codegen  --interface-prefix=com.deepin --generate-c-code=Building $<


 .PHONY : clean
clean :
	#rm gdbus_server gdbus_client gdbus_server.o gdbus_client.o
	rm gdbus_server gdbus_client Building.c Building.h
