#include "my_string.h"

inline static struct string *str_alloc(size_t size)
{
	struct string *new = (struct string *)malloc(
			sizeof(struct string) + (size+1)*sizeof(char));

	new->length = size;
	return new;
}

inline static size_t char_len(const char *src)
{
	char *t = (char *)src;
	while (*t != '\0')
	{
		t++;
	}

	return (size_t)(t - src);
}

inline static void char_copy(const char *dest, const char *src)
{
	char *t1 = (char *)dest;
	char *t2 = (char *)src;

	while (*t2)
	{
		*t1++ = *t2++;
	}

	*t1 = '\0';
}

inline static void char_2copy(const char *dest, const char *s1, const char *s2)
{
	char *t1 = (char *)dest;
	char *t2 = (char *)s1;

	while (*t2)
	{
		*t1++ = *t2++;
	}

	t2 = (char *)s2;

	while (*t2)
	{
		*t1++ = *t2++;
	}

	*t1 = '\0';
}

struct string *char2str(const char *text)
{
	size_t length = char_len(text);
	struct string *str = str_alloc(length);

	char_copy(str->text, text);

	return str;
}

struct string *concate_char(struct string *src, const char *text)
{
	size_t length = src->length + char_len(text);

	struct string *new = str_alloc(length);

	char_2copy(new->text, src->text, text);

	return new;
}

struct string *concate_str(struct string *src, struct string *dest)
{
	size_t length = src->length + dest->length;
	struct string *new = str_alloc(length);

	char_2copy(new->text, src->text, dest->text);

	return new;
}

