CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wno-unused-function -I.

PROG = ids
OBJ = maze_mat.o my_string.o priority_queue.o my_list.o main.o ids.o

all: $(PROG)

priority_queue.o: priority_queue.c priority_queue.h
	$(CC) $(CFLAGS) -c $^

my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c $^

my_list.o: my_list.c my_list.h
	$(CC) $(CFLAGS) -c $^

maze_mat.o: maze_mat.c maze_mat.h
	$(CC) $(CFLAGS) -c $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

ids.o: ids/ids.c ids/ids.h
	$(CC) $(CFLAGS) -c $^

ids: $(OBJ)
	$(CC) $(CFLAGS) -o $@.exe $^

clean:
	rm -rf *.h.gch $(OBJ)
	rm -rf ids/*.h.gch
	rm -rf *.exe

run:
	./$(PROG).exe "texts/test(windows).txt"

valgrind:
	valgrind --leak-check=yes ./$(PROG).exe

