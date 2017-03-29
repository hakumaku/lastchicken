/*
 * Input: A sequence of n numbers
 * Ouput: A permutation of the input sequence
 * such that a1 <= a2 <= a3 <= ... <= an
 *
 * Pseudocode
 *
 * param:
 *	p: the initial index of the left subarray.
 *	q+1: it represents the last index of the left subarray.
 *	q: the initial index of the right subarray.
 *	r: the last index of its array.
 *
 * MERGE_SORT(A,p,r)
 *	if p < r
 *		q = [(p+r)/2]
 *		MERGE_SORT(A,p,q)
 *		MERGE_SORT(A,q+1,r)
 *		MERGE(A,p,q,r)
 *
 * (The above function will be invoked as MERGE_SORT(A, 1, A.length))
 *
 * MERGE(A,p,q,r):
 *	n1 = q - p + 1
 *	n2 = r - q
 *	let L[1..n1+1] and R[1..n2+1] be new arrays
 *	for i = 1 to n1
 *		L[i] = A[p + i - 1]
 *	for j = 1 to n2
 *		R[j] = A[q + j]
 *	L[n1 + 1] = SENTINEL_VALUE
 *	R[n2 + 1] = SENTINEL_VALUE
 *	i = 1, j = 1
 *	for k = p to r
 *		if L[i] <= R[j]
 *			A[k] = L[i]
 *			i = i + 1
 *		else
 *			A[k] = R[j]
 *			j = j + 1
 */

#include <stdio.h>
#include <stdlib.h>

#define SENTINEL_VALUE ((-1U)>>1)

/*
 * The following functions are based on pseudocode,
 * much easier to comprehend.
 */
void pseudo_msort(int *arr, size_t p, size_t r);
void pseudo_merge(int *arr, size_t p, size_t q, size_t r);

/*	Devised	*/
void merge_sort(int *arr, size_t len);
void msort_divide(int *arr, size_t p, size_t r);
void msort_merge(int *arr, size_t p, size_t q, size_t r);

/*
 * Not using SENTINEL_VALUE.
 * Just to show what the implementation looks like
 * if SENTINEL_VALUE is not given.
 */
void nsmerge_sort(int *arr, size_t len);
void nsmsort_divide(int *arr, size_t p, size_t r);
void nsmsort_merge(int *arr, size_t p, size_t q, size_t r);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len1 = sizeof(test1) / sizeof(int);
	int test2[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len2 = sizeof(test2) / sizeof(int);
	int test3[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len3 = sizeof(test3) / sizeof(int);
	
	pseudo_msort(test1, 0, len1-1);
	for(int i = 0; i < len1; i++)
		printf("%d ", test1[i]);
	putchar('\n');

	merge_sort(test2, len2);
	for(int i = 0; i < len2; i++)
		printf("%d ", test2[i]);
	putchar('\n');

	nsmerge_sort(test3, len3);
	for(int i = 0; i < len3; i++)
		printf("%d ", test3[i]);
	putchar('\n');

	return 0;
}
/*
 * Do not get perplexed with its parameters.
 * C always subscripts from 0, not 1,
 * to n-1, not n, or A.length.
 */
void pseudo_msort(int *arr, size_t p, size_t r)
{
	if(p < r)
	{
		size_t q = (p + r) >> 1;
		pseudo_msort(arr, p, q);
		pseudo_msort(arr, q+1, r);
		pseudo_merge(arr, p, q, r);
	}
}
void pseudo_merge(int *arr, size_t p, size_t q, size_t r)
{
	size_t len1 = q - p + 1;
	size_t len2 = r - q;
	int i = 0, j = 0, k = p;
	int *left = NULL, *right = NULL;
	left = (int *)calloc(len1+1, sizeof(int));
	right = (int *)calloc(len2+1, sizeof(int));

	for(; i < len1; i++)
		left[i] = arr[p + i];
	left[len1] = SENTINEL_VALUE;

	for(; j < len2; j++)
		right[j] = arr[q + 1 + j];
	right[len2] = SENTINEL_VALUE;

	for(i = j = 0; k <= r; k++)
	{
		if(left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
	}

	free(left);
	free(right);
}

/*	Just a wrapper	*/
void merge_sort(int *arr, size_t len)
{
	msort_divide(arr, 0, len-1);
}
/*	Dividing	*/
void msort_divide(int *arr, size_t p, size_t r)
{
	if(p < r)
	{
		size_t q = (p + r) >> 1;
		/*	Left subarray	*/
		msort_divide(arr, p, q);
		/*	Right subarray	*/
		msort_divide(arr, q+1, r);
		/*	Merge them	*/
		msort_merge(arr, p, q, r);
	}
}
/*	Merging	*/
void msort_merge(int *arr, size_t p, size_t q, size_t r)
{
	/*
	 * Note that it's using len2, which is 'r - q', not len1.
	 * The reason is based on len1 >= len2.
	 */
	size_t len = r - q;
	int i = 0, j = 0, k = p;
	int *left = NULL, *right = NULL;
	left = (int *)calloc(len+2, sizeof(int));
	right = (int *)calloc(len+1, sizeof(int));

	/*	Copying it to subarrays	*/
	for(; i < len; i++)
	{
		/*	left: p ~ q , right: q+1 ~ r	*/
		left[i] = arr[p + i];
		right[i] = arr[q + 1 + i];
	}
	right[i] = SENTINEL_VALUE;
	/*
	 * Since it divides a target into
	 * p ~ q and q+1 ~ r, there are two cases
	 * in which the left subarray is one-element longer
	 * ,where q == p+1 holds,
	 * or the length of left is equal to that of right
	 * ,where p == q holds.
	 * It doesn't matter if you make it vice versa.
	 */
	if(p == q)
	{
		left[i] = SENTINEL_VALUE;
	}
	else
	{
		left[i] = arr[p + i];
		left[i + 1] = SENTINEL_VALUE;
	}
	/*	End of copying	*/

	/*	'k' is already initialized as 'p'	*/
	for(i = j = 0; k <= r; k++)
	{
		if(left[i] <= right[j])
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
	}

	free(left);
	free(right);
}

void nsmerge_sort(int *arr, size_t len)
{
	nsmsort_divide(arr, 0, len - 1);
}
void nsmsort_divide(int *arr, size_t p, size_t r)
{
	if(p < r)
	{
		size_t q = (p + r) >> 1;
		nsmsort_divide(arr, p, q);
		nsmsort_divide(arr, q+1, r);
		nsmsort_merge(arr, p, q, r);
	}
}
void nsmsort_merge(int *arr, size_t p, size_t q, size_t r)
{
	size_t len = r - q;
	int i = 0, j = 0, k = p;
	int *left = NULL, *right = NULL;
	left = (int *)calloc(len+1, sizeof(int));
	right = (int *)calloc(len, sizeof(int));

	for(; i < len; i++)
	{
		left[i] = arr[p + i];
		right[i] = arr[q + 1 + i];
	}
	if(p != q)
	{
		left[i] = arr[p + i];
	}

	for(i = j = 0; k <= r; k++)
	{
		/*
		 * 1) When 'right' has reached its boundary.
		 * 2) When 'left' has not reached its boundary yet,
		 *    and its value is the smaller.
		 */
		if(j == len || (i < len && left[i] <= right[j]))
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
	}

	free(left);
	free(right);
}