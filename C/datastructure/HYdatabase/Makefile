TARGET = main
LIBS =
CC = gcc
CFLAGS = -Wall -Wextra -Wshadow -O2 -std=c99 -Iinclude

.PHONY: default all clean

default: $(TARGET)
all: default

HEADER_PATH = include
SRC_PATH = src
UTIL_PATH = $(SRC_PATH)/util

MAIN_SRC = $(SRC_PATH)/main.c
MAIN_OBJ = $(patsubst %.c, %.o, $(MAIN_SRC))

SRC = $(wildcard $(SRC_PATH)/*.c)
SRC := $(filter-out $(MAIN_SRC), $(SRC))

HEADERS = $(wildcard $(HEADER_PATH)/*.h)
OBJECTS = $(patsubst %.c, %.o, $(SRC))

UTIL_HEADERS = $(wildcard $(UTIL_PATH)/*.h)
UTIL_OBJS = $(patsubst %.c, %.o, $(wildcard $(UTIL_PATH)/*.c))

$(UTIL_OBJS): $(wildcard $(UTIL_PATH)/*.c) $(UTIL_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJECTS): $(wildcard $(SRC_PATH)/*.c) $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(MAIN_OBJ) $(OBJECTS) $(UTIL_OBJS)
	$(CC) $(MAIN_OBJ) $(OBJECTS) $(UTIL_OBJS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(SRC_PATH)/*.o
	-rm -f $(UTIL_PATH)/*.o
	-rm -f $(TARGET)

