/*
 * An m*n 'Young Tableau'(pronounced [tab-low]) is
 * an m*n matrix such that the entries of each row are in sorted
 * order from left ro right and the entries of each column are in
 * sorted order from top to bottom.
 * Also, it seems there can be more than one solution for a Young Tableau,
 * which means there are a variety of ways of implementing it.
 * Most of this code is inspired by 'heap_sort.c'.
 * See 'heap_sort.c' first.
 * Two properties of Young Tableau used here:
 *	1) if tableau[m][n] == INF then it is NOT full.
 *	2) if tableau[1][1] == INF then it is EMPTY.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INF (-1U >> 1)
#define TRUE	1
#define FALSE	0

typedef struct {
	size_t row;
	size_t col;
	int *keys;
}young_t;

young_t *make_tableau(size_t m, size_t n);
void free_tableau(young_t *src);
void print_tableau(young_t *src);
void min_youngify(young_t *src, size_t i);
void build_youngtableau(young_t *src);

int young_extract_min(young_t *src);
int young_search(young_t *src);
void young_decrease_key(young_t *src, size_t i, int key);
void young_insert(young_t *src, int key);

int main(void)
{
	int cpy[35] = {
		51, 65, 76, 39, 47, 41, INF
		,43, 78, 36, 35, 55, 13, INF
		,77, 18, 64, 61, 32,  INF, INF
		,62, 81, 59, 31,  INF,  INF, INF
		,28, 38, 2, 87,  INF,  INF, INF
	};
	young_t *var1 = NULL;

	var1 = make_tableau(5, 7);

	memcpy(var1->keys, cpy, sizeof(cpy));
	print_tableau(var1);
	putchar('\n');

	build_youngtableau(var1);
	// [2, 13, 31, 32, 35, 41, INF]
	// [18, 36, 43, 47, 55, 76, INF]
	// [28, 39, 61, 65, 78, INF, INF]
	// [38, 59, 64, 77, INF, INF, INF]
	// [51, 62, 81, 87, INF, INF, INF]
	print_tableau(var1);
	putchar('\n');

	young_extract_min(var1);
	print_tableau(var1);
	putchar('\n');

	young_extract_min(var1);
	print_tableau(var1);
	putchar('\n');

	young_insert(var1, 1);
	print_tableau(var1);
	putchar('\n');

	young_insert(var1, 3);
	print_tableau(var1);
	putchar('\n');

	young_insert(var1, 5);
	print_tableau(var1);
	putchar('\n');

	young_insert(var1, 7);
	print_tableau(var1);
	putchar('\n');

	young_insert(var1, 9);
	print_tableau(var1);
	putchar('\n');

	young_insert(var1, 11);
	print_tableau(var1);
	putchar('\n');

	young_insert(var1, 13);
	print_tableau(var1);
	putchar('\n');

	young_insert(var1, 15);
	print_tableau(var1);
	putchar('\n');

	free_tableau(var1);
	return 0;
}

young_t *make_tableau(size_t m, size_t n)
{
	young_t *new = NULL;
	new = (young_t *)calloc(1, sizeof(young_t));
	new->row = m;
	new->col = n;
	new->keys = (int *)calloc(m*n, sizeof(int));
	for(size_t i = 0, length = m*n; i < length; i++)
	{
		new->keys[i] = INF;
	}

	return new;
}
void free_tableau(young_t *src)
{
	if(src)
	{
		if(src->keys)
			free(src->keys);
		free(src);
	}
}
void print_tableau(young_t *src)
{
	size_t row_length = src->row;
	size_t col_length = src->col;
	size_t stride = 0;
	for(size_t i = 0, j = 0; i < row_length; i++)
	{
		putchar('[');
		for(j = 0; j < col_length-1; j++)
		{
			if(src->keys[stride+j] != INF)
				printf("%3d, ", src->keys[stride+j]);
			else
				printf("INF, ");
		}
		if(src->keys[stride+j] != INF)
			printf("%3d]\n", src->keys[stride+j]);
		else
			printf("INF]\n");
		stride += col_length;
	}
}
/*
 * [i-col-1] [i-col] [i-col+1]
 * [ i - 1 ] [  i  ] [ i + 1 ]
 * [i+col-1] [i+col] [i+col+1]
 */
void min_youngify(young_t *src, size_t i)
{
	size_t down = 0;
	size_t right = 0;
	size_t smallest = i;
	size_t col = src->col;
	/*
	 * If it acceeds the size of column.
	 * Otherwise, it would compare with the first
	 * element of the next column if it was the last element.
	 * [O][O][O][O][X]
	 * [O][O][O][O][X]
	 * [O][O][O][O][X]
	 * [O][O][O][O][X]
	 * [O][O][O][O][X]
	 */
	if((i+1) % col)
	{
		right = i+1;
		if(src->keys[right] < src->keys[smallest])
			smallest = right;
	}
	/*
	 * If it acceeds the size of row.
	 * [O][O][O][O][O]
	 * [O][O][O][O][O]
	 * [O][O][O][O][O]
	 * [O][O][O][O][O]
	 * [X][X][X][X][X]
	 */
	if(i < col * (src->row-1))
	{
		down = i+col;
		if(src->keys[down] < src->keys[smallest])
			smallest = down;
	}

	if(smallest != i)
	{
		int temp = src->keys[i];
		src->keys[i] = src->keys[smallest];
		src->keys[smallest] = temp;
		min_youngify(src, smallest);
	}
}
/*
 * O(m * n * lg min(m,n))
 * [12][ ↗][ ↗][ ↗][ ↗][ ↗][ ↗]
 * [11][ ↗][ ↗][ ↗][ ↗][ ↗][ ↗]
 * [10][ ↗][ ↗][ ↗][ ↗][ ↗][ ↗]
 * [ 9][ ↗][ ↗][ ↗][ ↗][ ↗][ ↗]
 * [ 8][ ↗][ ↗][ ↗][ ↗][ ↗][ ↗]
 * [ 7][ ↗][ ↗][ ↗][ ↗][ ↗][ ↗]
 * [ 6][ 5][ 4][ 3][ 2][ 1][  ]
 */
void build_youngtableau(young_t *src)
{
	/*
	 * Hard to implement with 'size_t'.
	 * Really easy with a data type that is able to
	 * represent negative values.
	 */
	int row = (int)src->row;
	int col = (int)src->col;
	int si = 0, sj = 0, i = 0, j = 0;
	/*	← ← ← ← ←	*/
	si = col * (row-1);
	sj = col-2;
	while(sj >= 0)
	{
		i = si;
		j = sj;
		while(i >= 0 && j < col)
		{
			if(src->keys[i+j] != INF)
				min_youngify(src, (size_t)(i+j));
			i -= col;
			j++;
		}
		sj--;
	}
	/*	↑ ↑ ↑ ↑ ↑	*/
	si -= col;
	sj = 0;
	while(si >= 0)
	{
		i = si;
		j = sj;
		while(i >= 0 && j < col)
		{
			if(src->keys[i+j] != INF)
				min_youngify(src, (size_t)(i+j));
			i -= col;
			j++;
		}
		si -= col;
	}
}

int young_extract_min(young_t *src)
{
	if(src->keys[0] == INF)
	{
		printf("The young tableau is empty.\n");
		return 0;
	}
	int min = src->keys[0];
	src->keys[0] = INF;
	min_youngify(src, 0);
	return min;
}
void young_decrease_key(young_t *src, size_t i, int key)
{
	if(key > src->keys[i])
	{
		printf("The new key is greater than current key.\n");
		return;
	}
	src->keys[i] = key;

	/*
	 * Unlike max heap, it does not have PARENT.
	 * Therefore, it has to exchange with either UP or LEFT.
	 */
	size_t col = src->col;
	size_t left = 0, up = 0;
	size_t largest = i;
	int temp = 0;
	while(1)
	{
		/*
		 * [X][O][O][O][O]
		 * [X][O][O][O][O]
		 * [X][O][O][O][O]
		 * [X][O][O][O][O]
		 * [X][O][O][O][O]
		 */
		if(i % col != 0)
		{
			left = i-1;
			if(src->keys[left] > src->keys[largest])
				largest = left;
		}
		/*
		 * [X][X][X][X][X]
		 * [O][O][O][O][O]
		 * [O][O][O][O][O]
		 * [O][O][O][O][O]
		 * [O][O][O][O][O]
		 */
		if(i >= col)
		{
			up = i-col;
			if(src->keys[up] > src->keys[largest])
				largest = up;
		}
		if(largest != i)
		{
			temp = src->keys[largest];
			src->keys[largest] = src->keys[i];
			src->keys[i] = temp;
			i = largest;
		}
		else
			break;
	}
}
void young_insert(young_t *src, int key)
{
	size_t last = src->row*src->col - 1;
	if(src->keys[last] != INF)
	{
		printf("The young tableau is full.\n");
		return;
	}
	young_decrease_key(src, last, key);
}
