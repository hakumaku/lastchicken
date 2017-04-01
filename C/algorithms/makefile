CC = gcc
CFLAGS = -g -march=native
TARGET = main
OBJECTS = merge_sort.o

output: $(OBJECTS)
	$(CC) $(CFLAGS) -o output $(OBJECTS)

merge_sort.o: $@
	$(CC) $(CFLAGS) -c merge_sort.c

clean:
	rm *.o