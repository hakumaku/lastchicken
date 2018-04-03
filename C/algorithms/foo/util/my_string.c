#include "my_string.h"

#define BUFFER_SIZE	4096

String *char_to_string(const char *text)
{
	if (text == NULL)
	{
		return NULL;
	}

	char *p = (char *)text;

	while (*p)
	{
		p++;
	}

	return nchar_to_string(text, p - (char *)text);
}

String *nchar_to_string(const char *text, size_t len)
{
	if (text == NULL || len == 0)
	{
		return NULL;
	}

	String *str = (String *)calloc(1, sizeof(String) + len + 1);
	str->len = len;

	char *p = str->text;
	char *s = (char *)text;

	for (size_t i = 0; i < len; i++)
	{
		*p = *s;
		p++;
		s++;
	}
	*p = '\0';

	return str;
}

String *read_ltos(FILE *fp)
{
	if (fp == NULL || feof(fp) > 0)
	{
		return NULL;
	}

	char *buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	char *bp = buf;
	unsigned buf_size = BUFFER_SIZE;
	/* Need to store the initial position of fp. */
	long pos = ftell(fp);

	while (true)
	{
		size_t nbytes = fread(buf, sizeof(char), BUFFER_SIZE, fp);

		if (nbytes == 0)
		{
			break;
		}

		while (*bp)
		{
			if (*bp == '\n')
			{
				break;
			}

			bp++;
		}

		if (*bp == '\n')
		{
			bp++;
			fseek(fp, pos + (bp-buf), SEEK_SET);
			break;
		}
		else
		{
			buf_size += BUFFER_SIZE;
			buf = (char *)realloc(buf, sizeof(char) * buf_size);
			bp = buf + buf_size - BUFFER_SIZE;
		}
	}

	String *str = nchar_to_string(buf, bp-buf);
	free(buf);

	return str;
}

void print_string(String *src)
{
	size_t len = src->len;
	char *p = src->text;

	for (size_t i = 0; i < len; i++)
	{
		putchar(*p);
		p++;
	}
}

