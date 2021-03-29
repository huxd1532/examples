.PHONY:clean all

CC=gcc
CFLAGS= -Wall -g

BIN=tcp_server tcp_client
all:$(BIN)

#%.o:%.c
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@


tcp_server: tcp_server.o
	$(CC) $(CFLAGS) -o $@ $^

tcp_client: tcp_client.o
	$(CC) $(CFLAGS) -o $@ $^


clean:
	rm -rf $(BIN) *.o 
