#ifndef MY_STRING_H

#define MY_STRING_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct string_data String;

struct string_data
{
	size_t len;
	char text[0];
};

String *char_to_string(const char *text);
String *nchar_to_string(const char *text, size_t len);
String *read_ltos(FILE *fp);
void print_string(String *src);

#endif

