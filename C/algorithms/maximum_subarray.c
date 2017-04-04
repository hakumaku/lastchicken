/*
 * The maximum-subarray problem is interesting
 * only when the array contains some negative numbers.
 *
 * Pseudocode
 * FIND_MAX_CROSSING_SUBARRAY(A,low,mid,high):
 *	left_sum = -Inf
 *	sum = 0
 *	for i = mid downto low
 *		sum = sum + A[i]
 *		if sum > left_sum
 *			left_sum = sum
 *			max_left = i
 *	right_sum = -Inf
 *	sum = 0
 *	for j = mid + 1 to high
 *		sum = sum + A[j]
 *		if sum > right_sum
 *			right_sum = sum
 *			max_right = j
 *	return (max_left, max_right, left_sum + right_sum)
 *
 * FIND_MAXIMUM_SUBARRAY(A,low,high):
 *	if high == low
 *		return (low,high,A[low])	//base case: only one element
 *	else
 *		mid = floor[(low+high)/2]
 *		(left_low,left_high,left_sum) = FIND_MAXIMUM_SUBARRAY(A,low,mid)
 *		(right_low,right_high,right_sum) = FIND_MAXIMUM_SBUARRAY(A,mid+1,high)
 *		(cross_low,cross_high,cross_sum) = FIND_MAX_CROSSING_SUBARRAY(A,low,mid,high)
 *		if left_sum >= right_sum and left_sum >= cross_sum
 *			return (left_low,left_high,left_sum)
 *		else if right_sum >= left_sum and right_sum >= cross_sum
 *			return (right_low,right_hgih,right_sum)
 *		else
 *			return (cross_low,cross_high,cross_sum)
 *
 * (The above function will be invoked as FIND_MAXIMUM_SUBARRAY(A, 1, A.length))
 * There are three approaches to it:
 *	1)Brute-force
 *	2)Divide-and-conquer (The above pseudocode)
 *	3)Kadane's algorithm
 *
 * Kadane's algorithm:
 *
 * Simple idea of the Kadane's algorithm is to look for
 * all positive contiguous segments of the array 
 */
#include <stdio.h>

#define INF (-1U >> 1)
#define NEG_INF (~INF)

/*
 * If you want to know indices with sum,
 * you should pass a data structure like this.
 */
typedef struct {
	size_t si;
	size_t li;
	int sum;
} subarr_t;

/*	Brute Force(O(n^2))	*/
int max_subarray_bf(int *arr, size_t len);
/*
 * Divide-and-conquer (The above pseudocode)
 * Be careful that its 'high' is NOT A.length.
 * It must be n-1, the last index.
 */
int max_subarray_dq(int *arr, size_t low, size_t high);
int max_crosssum(int *arr, size_t low, size_t mid, size_t high);
/*	Kadane's algorithm	*/
int max_subarray_kadane(int *arr, size_t len);


int main(void)
{
	//The answer is 6
	int test1[] = { -2, 1, -3, 4, -1, 2, 1, -5, 4};
	//The answer is 7
	int test2[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int len1 = sizeof(test1) / sizeof(int);
    int len2 = sizeof(test2) / sizeof(int);
    int ret1 = 0, ret2 = 0, ret3 = 0;
	ret1 = max_subarray_dq(test2, 0, len2-1);
	ret2 = max_subarray_bf(test2, len2);
	ret3 = max_subarray_kadane(test2, len2);

	printf("Divide-and-conquer: %d\n", ret1);
	printf("Brute-force: %d\n", ret2);
	printf("Kadane's algorithm: %d\n", ret3);

	return 0;
}
/*	Simple but inefficient	*/
int max_subarray_bf(int *arr, size_t len)
{
	int sum = NEG_INF;
	int sub_sum = 0;

	for(size_t i = 0; i < len; i++)
	{
		for (size_t j = i; j < len; j++)
		{
			sub_sum += arr[j];
			if(sum < sub_sum)
				sum = sub_sum;
		}
		sub_sum = 0;
	}
	return sum;
}
/*
 * Three of 'low', 'mid', and 'high'
 * all indicate indices of arr.
 */
int max_subarray_dq(int *arr, size_t low, size_t high)
{
	/*	Base case: when it has one element	*/
	if(low == high)
	{
		return arr[low];
	}
	else
	{
		/*
		 * Integer overflow can occur,
		 * but will not deal with it.
		 */
		size_t mid = (low + high) >> 1;
		int left_sum = 0, right_sum = 0, cross_sum = 0, ret = 0;

		left_sum = max_subarray_dq(arr, low, mid);
		right_sum = max_subarray_dq(arr, mid+1, high);
		cross_sum = max_crosssum(arr, low, mid, high);

		/*
		 * Finding the maximum of three.
		 * It's performed with cmov.
		 */
		ret = left_sum;
		if(ret < right_sum)
			ret = right_sum;
		if(ret < cross_sum)
			ret = cross_sum;
		return ret;
	}
}
int max_crosssum(int *arr, size_t low, size_t mid, size_t high)
{
	int sum = 0;
	int left_sum = NEG_INF;
	int right_sum = NEG_INF;
	size_t i = 0;
	/*
	 * Find left_sum
	 * from low ~ mid
	 * When 'i' is negative,
	 * comparing 'i' with 'low' which is of type size_t
	 * yields true.
	 */
	for(i = mid; i != (size_t)-1 && i >= low; i--)
	{
		sum += arr[i];
		if(sum > left_sum)
		{
			left_sum = sum;
			// left_index (if you want to keep its index on it.)
		}
	}
	/*
	 * Find right_sum
	 * from mid+1 ~ high
	 */
	sum = 0;
	for(i = mid+1; i <= high; i++)
	{
		sum +=  arr[i];
		if(sum > right_sum)
		{
			right_sum = sum;
			// right_index (if you want to keep its index on it.)
		}
	}

	return left_sum + right_sum;
}
/*
 * It is not valid,
 * if it has no positive elements.
 */
int max_subarray_kadane(int *arr, size_t len)
{
	int sum = NEG_INF, sub_sum = 0;
	for(size_t i = 0; i < len; i++)
	{
		sub_sum += arr[i];
		/*
		 * If it gets below 0, 
		 * it just throws it away.
		 */
		if(sub_sum < 0)
			sub_sum = 0;
		/*
		 * It can be done with "else if(sum < sub_sum)"
		 * ,but it seems it doesn't make big difference
		 * since it generates cmov instruction.
		 */
		if(sum < sub_sum)
			sum = sub_sum;
	}
	return sum;
}