/*
 * Substring:
 *	A string that occurs in another string.
 *	e.g) "Algo" is a substring of "Introduction to Algorithms"
 *	, and also a subsequence.
 *
 * Subsequence:
 *	A sequence which can be derived from another sequence 
 *	by deleting some elements without changing the order.
 *	e.g) "IntoAl" is a subsequence of "Introduction to Algorithms"
 *	, but not a substring.
 *
 *	
 * LCS_LENGTH(X,Y):
 *	m = X.length
 *	n = Y.length
 *	let b[1..m, 1..n] and c[0..m, 0..n] be new tables
 *	for i = 1 to n
 *		c[i,0] = 0
 *	for j = 0 to n
 *		c[0,j] = 0
 *	for i = 1 to m
 *		for j = 1 to n
 *			if X[i] == Y[j]
 *				c[i,j] = c[i-1,j-1]+1
 *				b[i,j] = "↖"
 *			elseif c[i-1,j] >= c[i,j-1]
 *				c[i,j] = c[i-1,j]
 *				b[i,j] = "↑"
 *			else
 *				c[i,j] = c[i,j-1]
 *				b[i,j] = "←"
 *	return c and b
 *
 * PRINT_LCS(b,X,i,j)
 *	if i == 0 and j == 0
 *		return
 *	if b[i,j] == "↖"
 *		PRINT_LCS(b,X,i-1,j-1)
 *		print X[i]
 *	elseif b[i,j] == "↑"
 *		PRINT_LCS(b,X,i-1,j)
 *	else
 *		PRINT_LCS(b,X,i,j-1)
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define STRING1	"ZxzzIntAlzzzyyy"
// #define STRING1	"ABCBDAB"
#define STRING2	"Introduction to Algorithms"
// #define STRING2	"BDCABA"

typedef struct
{
	size_t **table;
	char *str1;
	char *str2;
	size_t col;
	size_t row;
} lcs_t;

lcs_t *lcs_length(const char *str1, size_t len1, const char *str2, size_t len2);
lcs_t *lcs_length_index(const char *str1, size_t len1, const char *str2, size_t len2);
void print_lcs(lcs_t *src);
size_t read_lcs(char *buf, const char *str, size_t **table, size_t i, size_t j);
size_t read_lcs2(char *buf, const char *str, size_t **table, size_t i, size_t j);
lcs_t *new_lcs(const char *str1, size_t len1, const char *str2, size_t len2);
void free_lcs(lcs_t *src);

int main(void)
{
	size_t len1 = strlen(STRING1);
	size_t len2 = strlen(STRING2);

	lcs_t *foo = lcs_length_index(STRING1, len1, STRING2, len2);

	printf("string1: (%2ld)%s\nstring2: (%2ld)%s\n",
			len1, STRING1, len2, STRING2);
	for (size_t i = 0; i < len1+1; i++)
	{
		for (size_t j = 0; j < len2+1; j++)
		{
			printf("%ld ", foo->table[i][j]);
		}
		putchar('\n');
	}
	print_lcs(foo);

	free_lcs(foo);

	return 0;
}

lcs_t *lcs_length(const char *str1, size_t len1, const char *str2, size_t len2)
{
	lcs_t *lcs_table = new_lcs(str1, len1, str2, len2);

	size_t **cp = lcs_table->table + 1;
	size_t **col = lcs_table->table + lcs_table->col;
	size_t n = lcs_table->row;

	char *c1 = (char *)str1;
	while (cp < col)
	{
		size_t *rp = *cp + 1;
		size_t *left = *cp;
		size_t *up = *(cp-1) + 1;
		size_t *row = *cp + n;
		char *c2 = (char *)str2;
		while (rp < row)
		{
			if (*c1 == *c2)
			{
				*rp = *(up-1) + 1;
			}
			else
			{
				size_t v1 = *left; 
				size_t v2 = *up;
				*rp = v1 > v2 ? v1 : v2;
			}
			left++;
			up++;
			rp++;
			c2++;
		}
		cp++;
		c1++;
	}

	return lcs_table;
}
lcs_t *lcs_length_index(const char *str1, size_t len1, const char *str2, size_t len2)
{
	lcs_t *lcs_table = new_lcs(str1, len1, str2, len2);
	size_t **table = lcs_table->table;
	size_t m = lcs_table->col;
	size_t n = lcs_table->row;

	char *c1 = (char *)str1;
	for (size_t i = 1; i < m; i++)
	{
		char *c2 = (char *)str2;
		for (size_t j = 1; j < n; j++)
		{
			if (*c1 == *c2)
			{
				table[i][j] = table[i-1][j-1] + 1;
			}
			else
			{
				size_t v1 = table[i][j-1];
				size_t v2 = table[i-1][j];
				table[i][j] = v1 > v2 ? v1 : v2;
			}
			c2++;
		}
		c1++;
	}

	return lcs_table;
}
void print_lcs(lcs_t *src)
{
	size_t i = src->col;
	size_t j = src->row;
	size_t len = i < j ? i : j;
	char *buf = (char *)calloc(len+1, sizeof(char));
	char *str = NULL;

	if (i < j)
	{
		str = src->str1;
		len = read_lcs(buf, str, src->table, i-1, j-1);
	}
	else
	{
		str = src->str2;
		len = read_lcs2(buf, str, src->table, i-1, j-1);
	}
	buf[len] = '\0';

	printf("Longest Common Sequence: %s(%ld)\n", buf, len);

	free(buf);
}
/* A bit wrong. Needs modifying. */
size_t read_lcs(char *buf, const char *str, size_t **table, size_t i, size_t j)
{
	if (i == 0 || j == 0)
	{
		return 0;
	}
	size_t v1 = table[i][j];
	size_t v2 = table[i][j-1];
	size_t v3 = table[i-1][j];

	if (v1 > v2 && v1 > v3)
	{
		size_t index = read_lcs(buf, str, table, i-1, j-1);
		buf[index] = str[i-1];
		return index+1;
	}
	else if (v3 > v2)
	{
		return read_lcs(buf, str, table, i-1, j);
	}
	else
	{
		return read_lcs(buf, str, table, i, j-1);
	}
}
size_t read_lcs2(char *buf, const char *str, size_t **table, size_t i, size_t j)
{
	if (i == 0 || j == 0)
	{
		return 0;
	}
	size_t v1 = table[i][j];
	size_t v2 = table[i][j-1];
	size_t v3 = table[i-1][j];

	if (v1 > v2 && v1 > v3)
	{
		size_t index = read_lcs2(buf, str, table, i-1, j-1);
		buf[index] = str[j-1];
		return index+1;
	}
	else if (v3 > v2)
	{
		return read_lcs2(buf, str, table, i-1, j);
	}
	else
	{
		return read_lcs2(buf, str, table, i, j-1);
	}
}
lcs_t *new_lcs(const char *str1, size_t len1, const char *str2, size_t len2)
{
	lcs_t *new = (lcs_t *)calloc(1, sizeof(lcs_t));

	new->str1 = (char *)calloc(len1+1, sizeof(char));
	strcpy(new->str1, str1);
	new->str1[len1] = '\0';

	new->str2 = (char *)calloc(len2+1, sizeof(char));
	strcpy(new->str2, str2);
	new->str2[len2] = '\0';

	size_t m = len1+1;
	size_t n = len2+1;
	new->col = m;
	new->row = n;

	new->table = (size_t **)calloc(m, sizeof(size_t *));
	size_t **table = new->table;
	size_t **end = table + m;
	while (table < end)
	{
		*table  = (size_t *)calloc(n, sizeof(size_t));
		table++;
	}

	return new;
}
void free_lcs(lcs_t *src)
{
	size_t m = src->col;
	size_t n = src->row;
	size_t **table = src->table;
	size_t **end = table + m;

	while (table < end)
	{
		free(*table);
		table++;
	}

	free(src->str1);
	free(src->str2);
	free(src->table);
}
