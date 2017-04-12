/*
 * A straightforward and intuitive.
 * It takes O(n^3).
 *
 * Pseudocode
 * SQUARE_MATRIX_MULTIPLY(A,B):
 *	n = A.rows
 *	let C be a new n*n matrix
 *	for i = 1 to n
 *		for j = 1 to n
 *			cij = 0
 *			for k = 1 to n
 *				cij = cij + aik*bkj
 *	return C
 *
 * The following code has a time complexity of O(n^3) as the above.
 * Not used in practice.
 *
 * Pseudocode
 * SQUARE_MATRIX_MULTIPLY_RECURSIVE(A,B):
 *	n = A.rows
 *	let C be a new n*n matrix
 *	if n == 1
 *		C11 = A11 * B11
 *	else
 *		C11 = SQUARE_MATRIX_MULTIPLY_RECURSIVE(A11,B11)
 *			+ SQUARE_MATRIX_MULTIPLY_RECURSIVE(A12,B21)
 *		C12 = SQUARE_MATRIX_MULTIPLY_RECURSIVE(A11,B12)
 *			+ SQUARE_MATRIX_MULTIPLY_RECURSIVE(A12,B22)
 *		C21 = SQUARE_MATRIX_MULTIPLY_RECURSIVE(A21,B11)
 *			+ SQUARE_MATRIX_MULTIPLY_RECURSIVE(A22,B21)
 *		C22 = SQUARE_MATRIX_MULTIPLY_RECURSIVE(A21,B12)
 *			+ SQUARE_MATRIX_MULTIPLY_RECURSIVE(A22,B22)
 *	return C
 *
 * Strassen's algorithm has O(n^2807).
 * The key to this method is to make the recursion tree slightly
 * less bushy. Instead of performing eight recursive multiplication
 * it does only seven.
 * It might seem obscure that why it has
 * those S1 ~ S10 and that from which they are derived,
 * but it's mathematically come to so to reduce the number of steps
 * of recursion resulting in O(n^log7).
 * If you carefully add all the components of C11 ~ C22,
 * which are P1 ~ P7, it just boils down to
 * (A11*B11 + A12*B21), (A11*B12 + A12*B22),
 * (A21*B11 + A22*B21) and (A21*B12 + A22*B22).
 * Since it holds for the size of power of 2,
 * if that of the input is not equal to power of 2
 * the input needs adjusting:
 * it can be extended to the next power of 2 or to the least size m * 2^k
 * greater than the order of input, such that m < Q for Q
 * which is defined to be a certain point that the function
 * performs a standard implementation of multiplying matrices.
 * The former is deemed to be dynamic padding, which is inefficient,
 * the latter static padding, quite improved.
 * Also, the algorithm can be implemented in a variety.
 *
 * Pseudocode
 * SQUARE_MATRIX_MULTIPLY_STRASSEN(A,B):
 *	n = A.rows
 *	let C be a new n*n matrix
 *	if n == 1
 *		C11 = A11 * B11
 *	else
 *		S1 = B12 - B22
 *		S2 = A11 + A12
 *		S3 = A21 + A22
 *		S4 = B21 - B11
 *		S5 = A11 + A22
 *		S6 = B11 + B22
 *		S7 = A12 - A22
 *		S8 = B21 + B22
 *		S9 = A11 - A21
 *		S10 = B11 + B12
 *		P1 = SQUARE_MATRIX_MULTIPLY_STRASSEN(A11,S1)
 *		P2 = SQUARE_MATRIX_MULTIPLY_STRASSEN(S2,B22)
 *		P3 = SQUARE_MATRIX_MULTIPLY_STRASSEN(S3,B11)
 *		P4 = SQUARE_MATRIX_MULTIPLY_STRASSEN(A22,S4)
 *		P5 = SQUARE_MATRIX_MULTIPLY_STRASSEN(S5,S6)
 *		P6 = SQUARE_MATRIX_MULTIPLY_STRASSEN(S7,S8)
 *		P7 = SQUARE_MATRIX_MULTIPLY_STRASSEN(S9,S10)
 *		C11 = P5 + P4 - P2 + P6
 *		C12 = P1 + P2
 *		C21 = P3 + P4
 *		C22 = P5 + P1 - P3 - P7
 *	return C
 *
 *
 *
 * Coppersmith-Winogrand[Vi-no-grah-nd]'s algorithm
 *	-O(n^2.376)
 *	-According to wiki, it is theoretically faster
 *	but impractical, since it holds effective when it comes to
 *	matrices so large for modern hardware.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define ORDER			5
#define BIG_ORDER		18
#define BASE_BOUNDARY	7

/*
 * It contains its array and its order.
 * The purpose of this data structure is to
 * figure out how long its row is for subscripting
 * its elements. For instance, the algorithm can be done
 * with static parameters like "int arr[][COL]", and cast as
 * "foo(arr)". However, for portability, the function is
 * done with "int *arr" and
 * subscripting should be performed in
 * "arr[stride + j]" in which "stride" is equal to "row * i".
 */
typedef struct {
	int order;
	int *arr;
}mat_t;


/*	Straightforward and intuitive	*/
void smul_matrix(int a[][ORDER], int b[][ORDER], int c[][ORDER]);

/*	Improved	*/
void imul_matrix(int a[][BIG_ORDER], int b[][BIG_ORDER], int c[][BIG_ORDER]);

/*	Strassen's algorithm	*/
mat_t *make_empty_sqmat(size_t order);
void free_sqmat(mat_t *src);
/*	print_sqmat is not necessarily needed	*/
void print_sqmat(mat_t *src);
void stmul_matrix(mat_t *a, mat_t *b, mat_t *c);
size_t get_least_size(size_t order, size_t basecase_order);
void stmul_divide(mat_t *a, mat_t *b, mat_t *c);
void stmul_base(mat_t *a, mat_t *b, mat_t *c);

int main(void)
{
	/*	mat_c = mat_a * mat_b	*/
	int mat_a[][ORDER] =
	{
		{0, 1, 2, 3, 4},
		{5, 6, 7, 8, 9},
		{0, 1, 2, 3, 4},
		{5, 6, 7, 8, 9},
		{0, 1, 2, 3, 4}
	};
	int mat_b[][ORDER] =
	{
		{9, 8, 7, 6, 5},
		{4, 3, 2, 1, 0},
		{9, 8, 7, 6, 5},
		{4, 3, 2, 1, 0},
		{9, 8, 7, 6, 5}
	};
	int mat_c[ORDER][ORDER] = { 0 };

	/*	mat_f = mat_d * mat_e	*/
	int mat_d[BIG_ORDER][BIG_ORDER] = { 0 };
	int mat_e[BIG_ORDER][BIG_ORDER] = { 0 };
	int mat_f[BIG_ORDER][BIG_ORDER] = { 0 };

	/*	mat_i = mat_g * mat_h	*/
	mat_t *mat_g = NULL, *mat_h = NULL, *mat_i = NULL;

	mat_g = make_empty_sqmat(BIG_ORDER);
	mat_h = make_empty_sqmat(BIG_ORDER);
	mat_i = make_empty_sqmat(BIG_ORDER);

	for(size_t i = 0, row = 0; i < BIG_ORDER; i++)
	{
		row = BIG_ORDER * i;
		for(size_t j = 0; j < BIG_ORDER; j++)
		{
			mat_d[i][j] = 1;
			mat_e[i][j] = 2;
			mat_g->arr[row + j] = 1;
			mat_h->arr[row + j] = 2;
		}
	}
	
	smul_matrix(mat_a, mat_b, mat_c);
	printf("smul_matrix : \n");
	for(size_t i = 0, j = 0; i < ORDER; i++)
	{
		putchar('[');
		for(j = 0; j < ORDER-1; j++)
			printf("%3d ", mat_c[i][j]);
		printf("%3d]\n", mat_c[i][j]);
	}
	putchar('\n');
	
	imul_matrix(mat_d, mat_e, mat_f);
	printf("imul_matrix : \n");
	for(size_t i = 0, j = 0; i < BIG_ORDER; i++)
	{
		putchar('[');
		for(j = 0; j < BIG_ORDER-1; j++)
			printf("%3d ", mat_f[i][j]);
		printf("%3d]\n", mat_f[i][j]);
	}
	putchar('\n');

	stmul_matrix(mat_g, mat_h, mat_i);
	printf("stmul_matrix\n");
	print_sqmat(mat_i);

	free_sqmat(mat_g);
	free_sqmat(mat_h);
	free_sqmat(mat_i);

	return 0;
}

/*
 * All the matrices of parameters of functions below
 * are privately square matrices for simplicity,
 * which have the same number of rows as columns.
 *
 * Some might see "int sum = 0" is unnecessary,
 * but it is crucial that it decreases the number of
 * dereferencing memory.
 */
void smul_matrix(int a[][ORDER], int b[][ORDER], int c[][ORDER])
{
	int sum = 0;
	for(size_t i = 0; i < ORDER; i++)
	{
		for(size_t j = 0; j < ORDER; j++)
		{
			sum = 0;
			for(size_t k = 0; k < ORDER; k++)
			{
				sum += a[i][k] * b[k][j];
			}
			c[i][j] = sum;
		}
	}
}
/*
 * It takes advantage of spatial locality. (CS: APP pg681)
 * The function smul_matrix computes ordinarily one by one,
 * whereas to increase sptial locality
 * the following function imul_matrix makes use of
 * the entire row, a[i][k], when it loads.
 * Therefore, the inner most loop does NOT complete
 * computing when it is done,
 * but it does the entire single row of 'c' at the end of k-loop.
 * The forer is also known as ijk-product,
 * the latter ikj-product.
 */
void imul_matrix(int a[][BIG_ORDER], int b[][BIG_ORDER], int c[][BIG_ORDER])
{
	int row = 0;
	for(size_t i = 0; i < BIG_ORDER; i++)
	{
		for(size_t k = 0; k < BIG_ORDER; k++)
		{
			row = a[i][k];
			for(size_t j = 0; j < BIG_ORDER; j++)
			{
				c[i][j] += row * b[k][j];
			}
		}
	}
}

/*	Strassen's algorithm	*/
mat_t *make_empty_sqmat(size_t order)
{
	mat_t *new = NULL;
	new = (mat_t *)calloc(1, sizeof(mat_t));
	new->order = order;
	/*	Square matrix	*/
	new->arr = (int *)calloc(order*order, sizeof(int));
	/*	Exception should be handled, but it is ignored.	*/
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

	/*	Above all, check whether the order is suitable.	*/
	extended_order = get_least_size(a->order, BASE_BOUNDARY);

	if(extended_order > a->order)
	{
		/*	Extending	*/
		size_t order = a->order;
		size_t elements_size = order * order;

		pad_a = make_empty_sqmat(extended_order);
		pad_b = make_empty_sqmat(extended_order);

		/*	Copying	*/
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

		/*	Computing	*/
		stmul_divide(pad_a, pad_b, c);

		/*	Freeing	*/
		free_sqmat(pad_a);
		free_sqmat(pad_b);
	}
	/*	For the case it does not need padding.	*/
	else
	{
		stmul_divide(a, b, c);
	}
}
/*
 * It computes the least size of a matrix padded with zero.
 */
size_t get_least_size(size_t order, size_t basecase_order)
{
	size_t cnt = 0;
	while(basecase_order < order)
	{
		/*
		 * Dividing an even integer with adding one
		 * is harmless, since it always floors down.
		 */
		order++;
		order >>= 1;
		cnt++;
	}
	return order << cnt;
}
void stmul_divide(mat_t *a, mat_t *b, mat_t *c)
{
	/*	Base case	*/
	if(a->order <= BASE_BOUNDARY)
	{
		stmul_base(a, b, c);
	}
	/*	Divide-and-conquer	*/
	else
	{
		/*	s1 ~ s10, p1 ~ p7 AND a11, a22, b11 and b22	*/
		mat_t *s[21] = { NULL };
		size_t stride_size = a->order;
		size_t submat_order = stride_size >> 1;
		size_t stride_a = 0, stride_b = 0, stride_ret = 0;

		/*	Callocating 21 submatrices.	*/
		for(size_t i = 0; i < 21; i++)
		{
			s[i] = make_empty_sqmat(submat_order);
		}

		/*	B12 - B22	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size + submat_order;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[0]->arr[stride_ret + j] = b->arr[stride_a + j] - b->arr[stride_b + j];
			}
		}	
		/*	A11 + A12	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = i * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[1]->arr[stride_ret + j] = a->arr[stride_a + j] + a->arr[stride_b + j];
			}
		}
		/*	A21 + A22	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[2]->arr[stride_ret + j] = a->arr[stride_a + j] + a->arr[stride_b + j];
			}
		}
		/*	B21 - B11	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size;
			stride_b = i * stride_size;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[3]->arr[stride_ret + j] = b->arr[stride_a + j] - b->arr[stride_b + j];
			}
		}
		/*	A11 + A22	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[4]->arr[stride_ret + j] = a->arr[stride_a + j] + a->arr[stride_b + j];
			}
		}
		/*	B11 + B22	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[5]->arr[stride_ret + j] = b->arr[stride_a + j] + b->arr[stride_b + j];
			}
		}
		/*	A12 - A22	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size + submat_order;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[6]->arr[stride_ret + j] = a->arr[stride_a + j] - a->arr[stride_b + j];
			}
		}
		/*	B21 + B22	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size;
			stride_b = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[7]->arr[stride_ret + j] = b->arr[stride_a + j] + b->arr[stride_b + j];
			}
		}
		/*	A11 - A21	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = (i + submat_order) * stride_size;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[8]->arr[stride_ret + j] = a->arr[stride_a + j] - a->arr[stride_b + j];
			}
		}
		/*	B11 + B12	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			stride_b = i * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[9]->arr[stride_ret + j] = b->arr[stride_a + j] + b->arr[stride_b + j];
			}
		}
		/*	A11	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[10]->arr[stride_ret + j] = a->arr[stride_a + j];
			}
		}
		/*	A22	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[11]->arr[stride_ret + j] = a->arr[stride_a + j];
			}
		}
		/*	B11	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = i * stride_size;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[12]->arr[stride_ret + j] = b->arr[stride_a + j];
			}
		}
		/*	B22	*/
		for(size_t i = 0; i < submat_order; i++)
		{
			stride_ret = i * submat_order;
			stride_a = (i + submat_order) * stride_size + submat_order;
			for(size_t j = 0; j < submat_order; j++)
			{
				s[13]->arr[stride_ret + j] = b->arr[stride_a + j];
			}
		}

		/*	P1(s[14]) = A11 * S1	*/
		stmul_divide(s[10], s[0], s[14]);
		/*	P2(s[15]) = S2 * B22	*/
		stmul_divide(s[1], s[13], s[15]);
		/*	P3(s[16]) = S3 * B11	*/
		stmul_divide(s[2], s[12], s[16]);
		/*	P4(s[17]) = A22 * S4	*/
		stmul_divide(s[11], s[3], s[17]);
		/*	P5(s[18]) = S5 * S6	*/
		stmul_divide(s[4], s[5], s[18]);
		/*	P6(s[19]) = S7 * S8	*/
		stmul_divide(s[6], s[7], s[19]);
		/*	P7(s[20]) = S9 * S10	*/
		stmul_divide(s[8], s[9], s[20]);

		/*
		 * "stride_b" is reused, it is supposed to be
		 * named as "trimmed_order".
		 *
		 * For some cases, the result of "c" looks like:
		 *
		 * <------------extended__order------------>
		 * <-----1st loop-----><-2ndloop->
		 * ┌───────────────────┬─────────┬ ─ ─ ─ ─ ┐
		 * │                   │         │         |
		 * │                   │         │         |
		 * │                   │         │         |
		 * │       C11         │   C12   │         |
		 * │                   │         │         |
		 * │                   │         │         |
		 * │                   │         │         |
		 * ├───────────────────┼─────────┼ ─ ─ ─ ─ ┤
		 * │                   │         │         |
		 * │       C21         │   C22   │         |
		 * │                   │         │         |
		 * ├───────────────────┼─────────┘         |
		 * |                   |                   |
		 * |                   |                   |
		 * |                   |                   |
		 * └ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┴ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┘
		 * <---submat_order---> <---submat_order--->
		 *
		 */
		stride_size = c->order;
		stride_b = stride_size - submat_order;
		for(size_t i = 0, j = 0; i < submat_order; i++)
		{
			stride_ret = i * stride_size;
			stride_a = i * submat_order;
			/*
			 * C11 = P5 + P4 - P2 + P6
			 * s[18] + s[17] - s[15] - s[19]
			 */
			for(j = 0; j < submat_order; j++)
			{
				c->arr[stride_ret + j] = s[18]->arr[stride_a + j] + s[17]->arr[stride_a + j]
									- s[15]->arr[stride_a + j] + s[19]->arr[stride_a + j];
			}
			/*
			 * C12 = P1 + P2
			 * s[14] + s[15]
			 */
			stride_ret += submat_order;
			for(j = 0; j < stride_b; j++)
			{
				c->arr[stride_ret + j] = s[14]->arr[stride_a + j] + s[15]->arr[stride_a + j];
			}
		}
		/*	stride_b = stride_size - submat_order;	*/
		for(size_t i = 0, j = 0; i < stride_b; i++)
		{
			stride_ret = (i + submat_order) * stride_size;
			stride_a = i * submat_order;
			/*
			 * C21 = P3 + P4
			 * s[16] + s[17]
			 */
			for(j = 0; j < submat_order; j++)
			{
				c->arr[stride_ret + j] = s[16]->arr[stride_a + j] + s[17]->arr[stride_a + j];
			}
			/*
		 	 * C22 = P5 + P1 - P3 - P7
		 	 * s[18] + s[14] - s[16] - s[20]
		 	 */
			stride_ret += submat_order;
			for(j = 0; j < stride_b; j++)
			{
				c->arr[stride_ret + j] = s[18]->arr[stride_a + j] + s[14]->arr[stride_a + j]
									- s[16]->arr[stride_a + j] - s[20]->arr[stride_a + j];
			}
		}

		/*	Freeing s1 ~ s21	*/
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
			/*	a[i][k]	*/
			row = a->arr[stride_a + k];
			for(size_t j = 0; j < stride_size; j++)
			{
				/*	c[i][j] & b[k][j]	*/
				c->arr[stride_a + j] += row * b->arr[stride_b + j];
			}
		}
	}
}