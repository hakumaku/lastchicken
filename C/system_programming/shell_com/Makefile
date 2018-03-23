CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wno-unused-function

PROG = shell_com.out
OBJ = shell_com.o

all: $(PROG)

shell_com.o: shell_com.c
	$(CC) $(CFLAGS) -c $^

shell_com.out: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf *.h.gch $(OBJ)
	rm -rf *.out

run:
	./$(PROG)

