CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wno-unused-function

# Binary Tree (recursive)
DIR1 = bitree_rec
SRC1 := $(addprefix $(DIR1)/, bitree_rec.c bitree_rec.h)
MAIN1 := $(addprefix $(DIR1)/, main.c)
OBJ1 = bitree_rec.o bitree_rec_main.o

bitree_rec_main.o: $(MAIN1)
	$(CC) $(CFLAGS) -o $@ -c $^

bitree_rec.o: $(SRC1)
	$(CC) $(CFLAGS) -c $^

# Binary Tree
DIR2 = bitree
SRC2 := $(addprefix $(DIR2)/, bitree.c bitree.h)
MAIN2 := $(addprefix $(DIR2)/, main.c)
OBJ2 = bitree.o bitree_main.o

bitree_main.o: $(MAIN2)
	$(CC) $(CFLAGS) -o $@ -c $^

bitree.o: $(SRC2)
	$(CC) $(CFLAGS) -c $^

# AVL Tree (recursive)
DIR3 = avltree_rec
SRC3 := $(addprefix $(DIR3)/, avltree_rec.c avltree_rec.h)
MAIN3 := $(addprefix $(DIR3)/, main.c)
OBJ3 = avltree_rec.o avltree_rec_main.o

avltree_rec_main.o: $(MAIN3)
	$(CC) $(CFLAGS) -o $@ -c $^

avltree_rec.o: $(SRC3)
	$(CC) $(CFLAGS) -c $^

# AVL Tree
DIR4 = avltree_rec
SRC4 := $(addprefix $(DIR4)/, avltree.c avltree.h)
MAIN4 := $(addprefix $(DIR4)/, main.c)
OBJ4 = avltree.o avltree_main.o

avltree_main.o: $(MAIN4)
	$(CC) $(CFLAGS) -o $@ -c $^

avltree.o: $(SRC4)
	$(CC) $(CFLAGS) -c $^

# Binary Tree (new)
DIR5 = bitree_new
SRC5 := $(addprefix $(DIR5)/, bitree.c bitree.h)
MAIN5 := $(addprefix $(DIR5)/, main.c)
OBJ5 = bitree.o bitree_main.o

bitree_main.o: $(MAIN5)
	$(CC) $(CFLAGS) -o $@ -c $^

bitree.o: $(SRC5)
	$(CC) $(CFLAGS) -c $^

all: bitree_rec bitree avltree_rec

bitree_rec: $(OBJ1)
	$(CC) $(CFLAGS) -o $@.out $^

bitree: $(OBJ2)
	$(CC) $(CFLAGS) -o $@.out $^

avltree_rec: $(OBJ3)
	$(CC) $(CFLAGS) -o $@.out $^

avltree: $(OBJ4)
	$(CC) $(CFLAGS) -o $@.out $^

bitree_new: $(OBJ5)
	$(CC) $(CFLAGS) -o $@.out $^

clean:
	rm -f *.o
	rm -f $(DIR1)/*.h.gch
	rm -f $(DIR2)/*.h.gch
	rm -f $(DIR3)/*.h.gch
	rm -f $(DIR5)/*.h.gch

