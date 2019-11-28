all : bus-service bus-client 
.PHONY : all
LIB_INC=$(shell pkg-config --cflags libsystemd)
CFLAGS+=$(LIB_INC)
LIB = $(shell pkg-config --libs libsystemd)
LIBS+=$(LIB)

bus-service : bus-service.o
	cc -o bus-service $(CFLAGS) $(LIBS) $<


bus-client : bus-client.o
	cc -o bus-client $(CFLAGS) $(LIBS) $<


bus-service.o : bus-service.c
	cc -c bus-service.c

bus-client.o : bus-client.c
	cc -c bus-client.c

 .PHONY : clean
clean :
	rm bus-service bus-service.o bus-client bus-client.o
