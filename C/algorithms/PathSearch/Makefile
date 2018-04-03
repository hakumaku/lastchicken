CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wno-unused-function -I. -I./util

PROG = ids gbs ass
OBJ = maze_mat.o my_string.o priority_queue.o my_list.o main.o

all: $(PROG)

priority_queue.o: util/priority_queue.c util/priority_queue.h
	$(CC) $(CFLAGS) -c $^

my_string.o: util/my_string.c util/my_string.h
	$(CC) $(CFLAGS) -c $^

my_list.o: util/my_list.c util/my_list.h
	$(CC) $(CFLAGS) -c $^

maze_mat.o: maze_mat.c maze_mat.h
	$(CC) $(CFLAGS) -c $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

ids.o: ids/ids.c ids/ids.h
	$(CC) $(CFLAGS) -c $^

ids: $(OBJ) ids.o
	$(CC) $(CFLAGS) -o $@.exe $^

gbs.o: gbs/gbs.c gbs/gbs.h
	$(CC) $(CFLAGS) -c $^

gbs: $(OBJ) gbs.o
	$(CC) $(CFLAGS) -o $@.exe $^

ass.o: ass/ass.c ass/ass.h
	$(CC) $(CFLAGS) -c $^

ass: $(OBJ) ass.o
	$(CC) $(CFLAGS) -o $@.exe $^

clean:
	rm -rf *.h.gch $(OBJ) ids.o gbs.o ass.o
	rm -rf ids/*.h.gch
	rm -rf gbs/*.h.gch
	rm -rf ass/*.h.gch
	rm -rf util/*.h.gch
	rm -rf *.exe

run_ids:
	./ids.exe "texts/test(windows).txt"

valgrind_ids:
	valgrind --leak-check=yes ./ids.exe

run_gbs:
	./gbs.exe "texts/test(windows).txt"

valgrind_gbs:
	valgrind --leak-check=yes ./gbs.exe

run_ass:
	./ass.exe "texts/test(windows).txt"

valgrind_ass:
	valgrind --leak-check=yes ./ass.exe

