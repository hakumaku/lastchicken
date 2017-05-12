/*
 * Pseudocode
 * PERMUTE_BY_SORTING(A):
 *	n = A.length
 *	let P[1..n] be a new array
 *	for i = 1 to n
 *		P[i] = RANDOM(1,n^3)
 *	sort A, using P as sort keys
 *
 * Pseudocode
 * RANDOMIZE_IN_PLACE(A):
 *	n = A.length
 *	for i = 1 to n
 *		swap A[i] with A[RANDOM(i,n)]
 *
 * Consider follwing implementations:
 * 1)
 * PERMUTE_WITHOUT_INDENTITY(A):
 *	n = A.length
 *	for i = 1 to n
 *		swap A[i] with A[RANDOM(i+1,n)]
 * 2)
 * PERMUTE_WITH_ALL(A):
 *	n = A.length
 *	for i = 1 to n
 *		swap A[i] with A[RANDOM(1,n)]
 * Those do not produce a uniform random permutation.
 *
 * (Not implemented.)
 * Pseudocode
 * RANDOM_SAMPLE(m,n):
 *	if m == 0
 *		return Ø
 *	else
 *		S = RANDOM_SAMPLE(m-1,n-1)
 *		if i ∈ S
 *			S = S ∪ {n}
 *		else
 *			S = S ∪ {i}
 *		return S
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t random(size_t a, size_t b);
void permute_by_sorting(int *arr, size_t len);
void randomize_in_place(int *arr, size_t len);

int main(void)
{
	int arr1[20] = { 0 };
	int arr2[20] = { 0 };

	for(int i = 0; i < 20; i++)
	{
		arr1[i] = i;
		arr2[i] = i;
	}

	permute_by_sorting(arr1, 20);
	for(int i = 0; i < 20; i++)
		printf("%d ", arr1[i]);
	putchar('\n');

	randomize_in_place(arr2, 20);
	for(int i = 0; i < 20; i++)
		printf("%d ", arr2[i]);
	putchar('\n');

	return 0;
}
/*
 * Suppose, RAND_MAX == 10
 * and see what happens when mod operator is applied:
 * For 0, 3, 6, or 9  in which rand()%3 == 0, P(0) == 4/11
 * For 1, 4, 7, or 10 in which rand()%3 == 1, P(1) == 4/11
 * For 2, 5, or 8 in which rand()%3 == 2, P(2) == "3/11"
 * There exist more secure and more uniformly distributed
 * random number generator functions.
 *
 * The function repeateadly invokes rand()
 * until it gets a value in a desired range.
 * It removes % operator bias resulting in
 * quite uniformly distributed values.
 * It returns a value in [a, b).
 */
size_t random(size_t a, size_t b)
{
	size_t ret = 0;
	size_t range = b - a;
	if(b < a)
	{
		/*	Inappropriate inputs	*/
		return 0;
	}

	do {
		ret = rand();
	} while(ret >= (RAND_MAX - RAND_MAX % range));

	return (ret % range) + a;
}
void permute_by_sorting(int *arr, size_t len)
{
	int *keys = NULL;
	int keys_smaller = 0, temp = 0;
	size_t cubic = len * len * len;
	keys = (int *)calloc(len, sizeof(int));

	srand(time(NULL));
	for(size_t i = 0; i < len; i++)
		keys[i] = random(0, cubic);

	/*
	 * Insertion Sort(Non-decreasing)
	 * Sorting keys and src at once.
	 */
	for(size_t i = 1, j = 0; i < len; i++)
	{
		temp = arr[i];
		keys_smaller = keys[i];	
		for(j = i-1; j != (size_t)-1 && keys[j] < keys_smaller; j--)
		{
			keys[j+1] = keys[j];
			arr[j+1] = arr[j];
		}
		keys[j+1] = keys_smaller;
		arr[j+1] = temp;
	}

	free(keys);
}

void randomize_in_place(int *arr, size_t len)
{
	int temp = 0, rand_index = 0;
	srand(time(NULL));
	for(size_t i = 0; i < len; i++)
	{
		/*	The range i~len is imperative.	*/
		rand_index = random(i, len);
		temp = arr[i];
		arr[i] = arr[rand_index];
		arr[rand_index] = temp;
	}
}