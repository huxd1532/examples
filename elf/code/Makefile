all: elf_test
CFLAGS+= -g

elf_test: elf_test.o elf_handle.o
	cc -o elf_test $(CFLAGS) $^

clean:
	rm -f elf_test *.o
