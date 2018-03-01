CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wno-unused-function

PROG = bintree
OBJ = bintree.o main.o

all: $(PROG)

bintree.o: bintree.c bintree.h
	$(CC) $(CFLAGS) -c $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

bintree: $(OBJ)
	$(CC) $(CFLAGS) -o $@.out $^

clean:
	rm -rf *.h.gch $(OBJ)
	rm -rf *.out

run:
	./$(PROG).out

