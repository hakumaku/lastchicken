CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wno-unused-function

PROG = avltree
OBJ = avltree.o main.o

all: $(PROG)

avltree.o: avltree.c avltree.h
	$(CC) $(CFLAGS) -c $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

avltree: $(OBJ)
	$(CC) $(CFLAGS) -o $@.out $^

clean:
	rm -rf *.h.gch $(OBJ)
	rm -rf *.out

run:
	./$(PROG).out

