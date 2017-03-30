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
 *	1)brute-force
 *	2)divide-and-conquer (The above pseudocode)
 *	3)Kadane's algorithm
 */
#include <stdio.h>

#define INF (-1U >> 1)
#define NEG_INF (~INF)

typedef struct subarr_t{
	size_t si;
	size_t li;
	int sum;
} subarr_t;

int max_crosssum(int *arr, size_t low, size_t mid, size_t high);
int max_subarray(int *arr, size_t low, size_t high);

int int main(void)
{
	/* code */
	return 0;
}
int max_crosssum(int *arr, size_t low, size_t mid, size_t high)
{
	int left_sum = NEG_INF, right_sum = NEG_INF;
	int sum = 0, i = 0;
	/*
	 * Find left_sum
	 * from mid ~ low
	 */
	for(i = mid; i >= low; i--)
	{
		sum += arr[i];
		if(sum > left_sum)
		{
			left_sum = sum;
			// left_index
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
			// right_index;
		}
	}

	return left_sum + right_sum;
}
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
int max_subarray(int *arr, size_t low, size_t high)
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
		int left_sum = 0, right_sum = 0, cross_sum = 0;
		int ret1 = 0, ret2 = 0;
		left_sum = max_subarray(arr, low, mid);
		right_sum = max_subarray(arr, mid+1, high);
		cross_sum = max_crosssum(arr, low, mid, high);
		/*	Finding maximum of three	*/
		ret1 = left_sum < right_sum ? right_sum : left_sum;
		ret2 = right_sum < cross_sum ? cross_sum : right_sum;
		return ret < cross_sum ? cross_sum : ret;
	}
}