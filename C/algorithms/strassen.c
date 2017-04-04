/*
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
 * SQUARE_MATRIX_MULTIPLY_RECURSIVE(A,B):
 *	n = A.rows
 *	let C be a new n*n matrix
 *	if n == 1
 *		c11 = a11 * b11
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
 * Strassen's algorithm
 *	-O(n^2.807)
 *
 * Coppersmith-Winogrand[Vi-no-grah-nd]'s algorithm
 *	-O(n^2.376)
 *	-According to wiki, it is theoretically faster
 *	but impractical, since it holds effective when it comes to
 *	matrices so large for modern hardware.
 *
 */

#include <stdio.h>

#define ORDER 5

/*	Straightforward and intuitive	*/
void smul_matrix(int a[][ORDER], int b[][ORDER], int c[][ORDER]);
/*	Improved	*/
void imul_matrix(int a[][ORDER], int b[][ORDER], int c[][ORDER]);

int main(void)
{
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
	int mat_d[ORDER][ORDER] = { 0 };

	smul_matrix(mat_a, mat_b, mat_c);

	for(size_t i = 0, j = 0; i < ORDER; i++)
	{
		putchar('[');
		for(j = 0; j < ORDER-1; j++)
			printf("%3d ", mat_c[i][j]);
		printf("%3d]\n", mat_c[i][j]);
	}

	putchar('\n');

	imul_matrix(mat_a, mat_b, mat_d);

	for(size_t i = 0, j = 0; i < ORDER; i++)
	{
		putchar('[');
		for(j = 0; j < ORDER-1; j++)
			printf("%3d ", mat_d[i][j]);
		printf("%3d]\n", mat_d[i][j]);
	}

	return 0;
}

/*
 * The matrix must be a square matrix
 * which has the same number of rows as columns.
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
 * The function smuL_matrix computes ordinarily one by one 
 * whereas to increase sptial locality
 * the following function imul_matrix makes use of
 * the entire row, a[i][k], when it loads.
 * Therefore, the inner most loop does NOT complete
 * computing when it is done,
 * but it does the entire single row of 'c' at the end of k-loop.
 */
void imul_matrix(int a[][ORDER], int b[][ORDER], int c[][ORDER])
{
	int row = 0;
	for(size_t i = 0; i < ORDER; i++)
	{
		for(size_t k = 0; k < ORDER; k++)
		{
			row = a[i][k];
			for(size_t j = 0; j < ORDER; j++)
			{
				c[i][j] += row * b[k][j];
			}
		}
	}
}