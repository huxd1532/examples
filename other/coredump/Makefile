CC = gcc
CFLAGS = -wall -g

BIN=test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test:test.o:
	$(CC) $(CFLAGS) -o test test.o

.PHONY : clean 
clean:
	rm -f $(BIN) *.o


