#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ORDER			1000
#define TRIAL			10
#define BASE_BOUNDARY	50
/*
 * intel(R) Core(TM) i5-6200U CPU @ 2.30GHz 2.40GHz
 * gcc -march=native strassen_test.c
 *
 * The following test is NOT PRECISE, (and surely wrong)
 * just couple of minutes of running code is all of it.
 * Though, it can be implicitly showing that
 * Strassen's algorithm is efficient as far as
 * couping with matrices of an enormous order,
 * (just as other source saying)
 * and dividing it until the last element of a matrix
 * does not lead to a good performance, but it rather aggravates.
 * IMO, it seems that modern cpu can lightly deal with
 * matrices of order circa 100, thus the appropriate point
 * when to stop the process of dividng and implement the standard way
 * should be so much rougly around 100.
 *
 * ORDER 200, TRIAL 10
 *
 *	  4: 4.839 ~ 5.478
 *	  5: 4.799 ~ 5.512
 *	  7: 1.859 ~ 2.062
 *	  9: 1.768 ~ 1.876
 *	 11: 1.750 ~ 1.876
 *	 15: 0.985 ~ 1.062
 *	 17: 0.985 ~ 1.000
 *	 21: 0.953 ~ 1.000
 *	 25: 0.859 ~ 0.875
 *	 30: 0.844 ~ 0.907
 *	 40: 0.865 ~ 0.937
 *	 50: 0.800 ~ 0.890
 *	 70: 0.859 ~ 0.875
 *	100: 0.922 ~ 0.953
 *	200: 0.937 ~ 1.015
 *
 * ORDER 500, TRIAL 10
 *
 *	500: 12.208
 *	250: 11.018
 *	100: 9.445
 *	 50: 10.049
 *	 20: 10.192
 *	 10: 13.629
 *	120: 9.442
 *
 * ORDER 1000, TRIAL 10
 *
 *	1000: 93.814
 *	 100: 63.281
 *	  50: 65.091
 */

typedef struct {
	int order;
	int *arr;
}mat_t;

mat_t *make_empty_sqmat(size_t order);
void free_sqmat(mat_t *src);
void print_sqmat(mat_t *src);
void stmul_matrix(mat_t *a, mat_t *b, mat_t *c);
size_t get_least_size(size_t order, size_t basecase_order);
void stmul_divide(mat_t *a, mat_t *b, mat_t *c);
void stmul_base(mat_t *a, mat_t *b, mat_t *c);

int main(void)
{
	clock_t s, e;
	mat_t *a = NULL, *b = NULL, *c = NULL;

	a = make_empty_sqmat(ORDER);
	b = make_empty_sqmat(ORDER);
	c = make_empty_sqmat(ORDER);

	for(size_t i = 0, row = 0; i < ORDER; i++)
	{
		row = ORDER * i;
		for(size_t j = 0; j < ORDER; j++)
		{
			a->arr[row + j] = 1;
			b->arr[row + j] = 2;
		}
	}

	s = clock();
	for (int i = 0; i < TRIAL; i++)
	{
		stmul_matrix(a, b, c);
	}
	e = clock();
	printf("stmul_matrix : %Lf\n", difftime(e, s) / CLOCKS_PER_SEC);

	return 0;
}

mat_t *make_empty_sqmat(size_t order)
{
	mat_t *new = NULL;
	new = (mat_t *)calloc(1, sizeof(mat_t));
	new->order = order;
	new->arr = (int *)calloc(order*order, sizeof(int));
	return new;
}
void free_sqmat(mat_t *src)
{
	if(src->arr)
		free(src->arr);
	free(src);
}
void print_sqmat(mat_t *src)
{
	size_t order = src->order;
	for(size_t i = 0, j = 0, stride = 0; i < order; i++)
	{
		stride = order * i;
		putchar('[');
		for(j = 0; j < order - 1; j++)
			printf("%3d ", src->arr[stride + j]);
		printf("%3d]\n", src->arr[stride + j]);
	}
	putchar('\n');
}
void stmul_matrix(mat_t *a, mat_t *b, mat_t *c)
{
	mat_t *pad_a = NULL;
	mat_t *pad_b = NULL;
	size_t extended_order = 0;

	extended_order = get_least_size(a->order, BASE_BOUNDARY);

	if(extended_order > a->order)
	{
		size_t order = a->order;
		size_t elements_size = order * order;

		pad_a = make_empty_sqmat(extended_order);
		pad_b = make_empty_sqmat(extended_order);

		for(size_t i = 0, stride_a = 0, stride_b = 0; i < order; i++)
		{
			stride_a = extended_order * i;
			stride_b = order * i;
			for(size_t j = 0; j < order; j++)
			{
				pad_a->arr[stride_a + j] = a->arr[stride_b + j];
				pad_b->arr[stride_a + j] = b->arr[stride_b + j];
			}
		}

		stmul_divide(pad_a, pad_b, c);

		free_sqmat(pad_a);
		free_sqmat(pad_b);
	}
	else
		stmul_divide(a, b, c);
}
size_t get_least_size(size_t order, size_t basecase_order)
{
	size_t cnt = 0;
	while(basecase_order < order)
	{
		order++;
		order >>= 1;
		cnt++;
	}
	return order << cnt;
}
void stmul_divide(mat_t *a, mat_t *b, mat_t *c)
{
	if(a->order <= BASE_BOUNDARY)
		stmul_base(a, b, c);
	else
	{
		mat_t *s[21] = { NULL };
		size_t stride_size = a->order;
		size_t submat_order = stride_size >> 1;
		size_t stride_a = 0, stride_b = 0, stride_ret = 0;

		for(size_t i = 0; i < 21; i++)
			s[i] = make_empty_sqmat(submat_order);

		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size + submat_order;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[0]->arr[stride_ret + j] = b->arr[stride_a + j] - b->arr[stride_b + j];
		}	
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = i * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[1]->arr[stride_ret + j] = a->arr[stride_a + j] + a->arr[stride_b + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[2]->arr[stride_ret + j] = a->arr[stride_a + j] + a->arr[stride_b + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size;
			stride_b = i * stride_size;
			for(size_t j = 0; j < submat_order; j++)
				s[3]->arr[stride_ret + j] = b->arr[stride_a + j] - b->arr[stride_b + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[4]->arr[stride_ret + j] = a->arr[stride_a + j] + a->arr[stride_b + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[5]->arr[stride_ret + j] = b->arr[stride_a + j] + b->arr[stride_b + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size + submat_order;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[6]->arr[stride_ret + j] = a->arr[stride_a + j] - a->arr[stride_b + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[7]->arr[stride_ret + j] = b->arr[stride_a + j] + b->arr[stride_b + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = (i + submat_order) * stride_size;
			for(size_t j = 0; j < submat_order; j++)
				s[8]->arr[stride_ret + j] = a->arr[stride_a + j] - a->arr[stride_b + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = i * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[9]->arr[stride_ret + j] = b->arr[stride_a + j] + b->arr[stride_b + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			for(size_t j = 0; j < submat_order; j++)
				s[10]->arr[stride_ret + j] = a->arr[stride_a + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[11]->arr[stride_ret + j] = a->arr[stride_a + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			for(size_t j = 0; j < submat_order; j++)
				s[12]->arr[stride_ret + j] = b->arr[stride_a + j];
		}
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
				s[13]->arr[stride_ret + j] = b->arr[stride_a + j];
		}

		stmul_divide(s[10], s[0], s[14]);
		stmul_divide(s[1], s[13], s[15]);
		stmul_divide(s[2], s[12], s[16]);
		stmul_divide(s[11], s[3], s[17]);
		stmul_divide(s[4], s[5], s[18]);
		stmul_divide(s[6], s[7], s[19]);
		stmul_divide(s[8], s[9], s[20]);

		stride_size = c->order;
		stride_b = stride_size - submat_order;
		for(size_t i = 0, j = 0; i < submat_order; i++)
		{
			stride_ret = i * stride_size;
			stride_a = i * submat_order;

			for(j = 0; j < submat_order; j++)
			{
				c->arr[stride_ret + j] = s[18]->arr[stride_a + j] + s[17]->arr[stride_a + j]
									- s[15]->arr[stride_a + j] + s[19]->arr[stride_a + j];
			}

			stride_ret += submat_order;
			for(j = 0; j < stride_b; j++)
				c->arr[stride_ret + j] = s[14]->arr[stride_a + j] + s[15]->arr[stride_a + j];
		}
		for(size_t i = 0, j = 0; i < stride_b; i++)
		{
			stride_ret = (i + submat_order) * stride_size;
			stride_a = i * submat_order;

			for(j = 0; j < submat_order; j++)
				c->arr[stride_ret + j] = s[16]->arr[stride_a + j] + s[17]->arr[stride_a + j];

			stride_ret += submat_order;
			for(j = 0; j < stride_b; j++)
			{
				c->arr[stride_ret + j] = s[18]->arr[stride_a + j] + s[14]->arr[stride_a + j]
									- s[16]->arr[stride_a + j] - s[20]->arr[stride_a + j];
			}
		}
		for(size_t i = 0; i < 21; i++)
			free_sqmat(s[i]);
	}
}
void stmul_base(mat_t *a, mat_t *b, mat_t *c)
{
	int row = 0;
	size_t stride_a = 0, stride_b = 0;
	size_t stride_size = a->order;

	for(size_t i = 0; i < stride_size; i++)
	{
		stride_a = stride_size * i;
		for(size_t k = 0; k < stride_size; k++)
		{
			stride_b = stride_size * k;
			row = a->arr[stride_a + k];
			for(size_t j = 0; j < stride_size; j++)
				c->arr[stride_a + j] += row * b->arr[stride_b + j];
		}
	}
}