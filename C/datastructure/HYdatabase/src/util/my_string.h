#ifndef __MY_STRING_H__
#define __MY_STRING_H__

#include <stdlib.h>

struct string
{
	size_t length;
	char text[];
};

/*
 * Convert char to string.
 */
struct string *char2str(const char *text);

/*
 * new = string + char
 */
struct string *concate_char(struct string *src, const char *text);

/*
 * new = string + string
 */
struct string *concate_str(struct string *src, struct string *dest);

#endif /* __MY_STRING_H__ */

