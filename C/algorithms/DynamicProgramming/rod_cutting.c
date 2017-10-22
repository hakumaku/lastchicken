/*
 * Rod-cutting problem:
 * Given a rod of length n inches and a table
 * of prices p[i] for i = 1, 2, ..., n, determine
 * the maximum revenue r[n] obtainable by cutting up
 * the rod and selling the pieces.
 *
 *
 * CUT_ROD(p,n):
 *	if n == 0
 *		return 0
 *	q = -INF
 *	for i = 1 to n
 *		q = max(q, p[i] + CUT_ROD(p, n-i))
 *	return q
 *
 * The above code will run in T(n) = O(2^n).
 *
 *
 * MEMOIZED_CUT_ROD(p,n):
 *	let r[0...n] be a new array
 *	for i = 0 to n
 *		r[i] = -INF
 *	return MEMOIZED_CUT_ROD_AUX(p,n,r)
 *
 * MEMOIZED_CUT_ROD_AUX(p,n,r)
 *	if r[n] >= 0
 *		return r[n]
 *	if n == 0
 *		q = 0
 *	else
 *		q = -INF
 *		for i = 1 to n
 *			q = max(q, p[i] + MEMOIZED_CUT_ROD_AUX(p,n-i,r))
 *	r[n] = q
 *	return q
 *
 * The number of invoking is significantly reduced due to
 * the memoized array.
 *
 * BOTTOM_UP_CUT_ROD(p,n):
 *	let r[0..n] be a new array
 *	r[0] = 0
 *	for j = 1 to n
 *		q = -INF
 *		for i = 1 to j
 *			q = max(q, p[i]+r[j-i])
 *		r[j] = q
 *	return r[n]
 *
 * (Why do all the implementation not have -INF?
 * I assume that the price cannot be 0.)
 */
#include <stdio.h>
#include <stdlib.h>

#define LENGTH		10

size_t cut_rod(size_t *table, size_t len);
size_t mcut_rod(size_t *table, size_t len);
size_t mcut_rod_aux(size_t *table, size_t len, size_t *memo);
size_t bucut_rod(size_t *table, size_t len);
size_t max(size_t a, size_t b);

static size_t count1 = 0;
static size_t count2 = 0;
static size_t count3 = 0;

int main(int argc, const char *argv[])
{
	size_t table[LENGTH] = {
		1, 5, 8, 9, 10,
		17, 17, 20, 24, 30
	};

	puts("table entries.");
	for (int i = 0; i < LENGTH; i++)
	{
		printf("%ld ", table[i]);
	}
	putchar('\n');

	printf("Result(cut_rod): \t%ld", cut_rod(table, LENGTH));
	printf("\t(called: %ld)\n", count1);

	printf("Result(mcut_rod): \t%ld", mcut_rod(table, LENGTH));
	printf("\t(called: %ld)\n", count2);

	printf("Result(bucut_rod): \t%ld", bucut_rod(table, LENGTH));
	printf("\t(called: %ld)\n", count3);

	return 0;
}

size_t cut_rod(size_t *table, size_t len)
{
	count1++;

	if (len == 0)
	{
		return 0;
	}

	size_t rev = 0;

	for (size_t i = 0; i < len; i++)
	{
		rev	= max(rev, table[i]+cut_rod(table, len-i-1));
	}
	
	return rev;
}
size_t mcut_rod(size_t *table, size_t len)
{
	size_t *memo = (size_t *)calloc(len, sizeof(size_t));
	size_t ret = mcut_rod_aux(table, len, memo);

	free(memo);

	return ret;
}
size_t mcut_rod_aux(size_t *table, size_t len, size_t *memo)
{
	count2++;

	if (len == 0)
	{
		return 0;
	}

	size_t known_value = memo[len-1];

	if (known_value > 0)
	{
		return known_value;
	}

	size_t rev = 0;

	for (size_t i = 0; i < len; i++)
	{
		rev = max(rev, table[i]+mcut_rod_aux(table, len-i-1, memo));
	}
	memo[len-1] = rev;

	return rev;
}
size_t bucut_rod(size_t *table, size_t len)
{
	count3++;
	size_t *temp = (size_t *)calloc(len+1, sizeof(size_t));
	size_t rev = 0;

	for (size_t i = 0; i < len; i++)
	{
		rev = 0;
		for (size_t j = 0; j <= i; j++)
		{
			rev = max(rev, table[j]+temp[i-j]);
		}
		temp[i+1] = rev;
	}

	rev = temp[len];

	free(temp);

	return rev;
}
size_t max(size_t a, size_t b)
{
	return a > b ? a : b;
}

