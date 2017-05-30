/*
 * param:
 *	p: the initial index of the left subarray.
 *	q: the last index of the left subarray.
 *	q+1: it represents the initial index of the right subarray.
 *	r: the last index of the right subarray.
 *
 * Pseudocode
 * MERGE_SORT(A,p,r)
 *	if p < r
 *		q = [(p+r)/2]
 *		MERGE_SORT(A,p,q)
 *		MERGE_SORT(A,q+1,r)
 *		MERGE(A,p,q,r)
 *
 * (The above function will be invoked as MERGE_SORT(A, 1, A.length))
 *
 * Pseudocode
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
 *
 * SENTINEL_VALUE makes it really easy to implement,
 * where the difficultiness comes from asymmetry of the length
 * of the left and the right.
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
 * Not using SENTINEL_VALUE(ns).
 * Just to show what the implementation looks like
 * if SENTINEL_VALUE is not given.
 */
void nsmerge_sort(int *arr, size_t len);
void nsmsort_divide(int *arr, size_t p, size_t r);
void nsmsort_merge(int *arr, size_t p, size_t q, size_t r);

/*
 * Much improved(new).
 * Much of explanation is omitted,
 * better see previous functions first.
 */
void nmerge_sort(int *arr, size_t len);
void nmsort_divide(int *arr, int *tmp, size_t p, size_t r);
void nmsort_merge(int *arr, int *tmp, size_t p, size_t q, size_t r);

int main(void)
{
	int test1[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len1 = sizeof(test1) / sizeof(int);
	int test2[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len2 = sizeof(test2) / sizeof(int);
	int test3[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len3 = sizeof(test3) / sizeof(int);
	int test4[] = {100, 99, 98, 32, 23, 12, 7, 8, 9, 3, 1};
	int len4 = sizeof(test4) / sizeof(int);

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

	nmerge_sort(test4, len4);
	for(int i = 0; i < len4; i++)
		printf("%d ", test4[i]);
	putchar('\n');

	return 0;
}
/*
 * Dividng step. Its name should be sth like 'divide'.
 * Do not get perplexed with its parameters: p, q, r.
 * C always subscripts from 0, not 1,
 * to n-1, not n, or A.length.
 */
void pseudo_msort(int *arr, size_t p, size_t r)
{
	if(p < r)
	{
		/*
		 * Integer overflow can occur,
		 * but will not deal with it.
		 */
		size_t q = (p + r) >> 1;
		/*	Left subarray	*/
		pseudo_msort(arr, p, q);
		/*	Right subarray	*/
		pseudo_msort(arr, q+1, r);
		/*	Merge them	*/
		pseudo_merge(arr, p, q, r);
	}
}
/*	Merging	*/
void pseudo_merge(int *arr, size_t p, size_t q, size_t r)
{
	size_t len1 = q - p + 1;
	size_t len2 = r - q;
	size_t i = 0, j = 0, k = p;
	int *left = NULL, *right = NULL;
	/*	Extra one more space for SENTINEL_VALUE	*/
	left = (int *)calloc(len1+1, sizeof(int));
	right = (int *)calloc(len2+1, sizeof(int));

	for(; i < len1; i++)
		left[i] = arr[p + i];
	left[len1] = SENTINEL_VALUE;

	for(; j < len2; j++)
		right[j] = arr[q+1 + j];
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
	/*
	 * Note that it is NOT casting 'len', but 'len-1'.
	 */
	msort_divide(arr, 0, len-1);
}
void msort_divide(int *arr, size_t p, size_t r)
{
	if(p < r)
	{
		size_t q = (p + r) >> 1;
		/*	[p,q]	*/
		msort_divide(arr, p, q);
		/*	[q+1,r]	*/
		msort_divide(arr, q+1, r);
		msort_merge(arr, p, q, r);
	}
}
void msort_merge(int *arr, size_t p, size_t q, size_t r)
{
	/*
	 * Note that it's using len2, which is 'r - q', not len1.
	 * The reason is based on len1 >= len2.
	 */
	size_t len = r - q;
	size_t i = 0, j = 0, k = p;
	int *left = NULL, *right = NULL;
	left = (int *)calloc(len+2, sizeof(int));
	right = (int *)calloc(len+1, sizeof(int));

	/*	Copying it to subarrays	*/
	for(; i < len; i++)
	{
		/*	left: p ~ q , right: q+1 ~ r	*/
		left[i] = arr[p + i];
		right[i] = arr[q+1 + i];
	}
	right[i] = SENTINEL_VALUE;
	/*
	 * Since it divides a target into
	 * p ~ q and q+1 ~ r, there are two cases
	 * in which the left subarray is one-element longer
	 * or the length of left is equal to that of right.
	 * It doesn't matter if you make it vice versa.
	 */
	if(r-q > q-p)
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
	nsmsort_divide(arr, 0, len-1);
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
	size_t len2 = r - q;
	size_t len1 = len2;
	size_t i = 0, j = 0, k = p;
	int *left = NULL, *right = NULL;
	int test = 0, v1 = 0, v2 = 0;
	left = (int *)calloc(len2+1, sizeof(int));
	right = (int *)calloc(len2, sizeof(int));

	for(; i < len2; i++)
	{
		left[i] = arr[p + i];
		right[i] = arr[q+1 + i];
	}
	if(r-q == q-p)
	{
		left[i] = arr[p + i];
		len1++;
	}
	i = j = 0;
	while(i < len1 && j < len2)
	{
		v1 = left[i];
		v2 = right[j];
		test = v1 <= v2;
		arr[k++] = test ? v1 : v2;
		i += test;
		j += (1-test);
	}
	while(i < len1)
		arr[k++] = left[i++];
	while(j < len2)
		arr[k++] = right[j++];

	free(left);
	free(right);
}

/*
 * It will not be allocating and freeing
 * again and again, instead, it will hold one as big as
 * the source until the end of its process.
 * Changed its loop-range; see that the arg is not 'len-1' but 'len'.
 */
void nmerge_sort(int *arr, size_t len)
{
	int *tmp = NULL;
	tmp = (int *)calloc(len, sizeof(int));

	nmsort_divide(arr, tmp, 0, len);

	free(tmp);
}
/*
 * Not so much different except that it carries 'tmp',
 * which has been pre-allocated.
 */
void nmsort_divide(int *arr, int *tmp, size_t p, size_t r)
{
	if(p+1 < r)
	{
		size_t q = (p + r) >> 1;
		/*	[p,q)	*/
		nmsort_divide(arr, tmp, p, q);
		/*	[q,r)	*/
		nmsort_divide(arr, tmp, q, r);
		nmsort_merge(arr, tmp, p, q, r);
	}
}
void nmsort_merge(int *arr, int *tmp, size_t p, size_t q, size_t r)
{
	/*	It will take advantage of conditional move.	*/
	int v1 = 0, v2 = 0, test = 0;
	/*	left index, right index, source index	*/
	size_t li = p, ri = q, si = p;

	while(li < q && ri < r)
	{
		v1 = arr[li];
		v2 = arr[ri];
		test = v1 <= v2;
		/*	Increment of source index occurs here.	*/
		tmp[si++] = test ? v1 : v2;
		/*	Whether li increases or ri increases	*/
		li += test;
		ri += (1-test);
	}
	/*	Copy rest of the left and the right subarray.	*/
	if(li < q)
	{
		do {
			tmp[si++] = arr[li++];
		} while(li < q);
	}
	else
	{
		do {
			tmp[si++] = arr[ri++];
		} while(ri < r);
	}
	// while(li < q)
	// 	tmp[si++] = arr[li++];
	// while(ri < r)
	// 	tmp[si++] = arr[ri++];

	/*	Write back the sorted result.	*/
	for(si = p; si < r; si++)
		arr[si] = tmp[si];
}
