CC			= gcc
CFLAGS	= -g
RM			= rm -f
TARGET	= main

default: all

all: deps
	$(CC) $(CFLAGS) main.c -o $(TARGET) memory.o chunk.o debug.o value.o vm.o compiler.o scanner.o

deps:
	$(CC) $(CFLAGS) -c src/memory.c src/chunk.c src/debug.c src/value.c src/vm.c src/compiler.c src/scanner.c

run:
	make
	echo "\n"
	./$(TARGET)
	echo "\n"
	make clean

clean:
		$(RM) main chunk.o debug.o memory.o value.o vm.o compiler.o scanner.o