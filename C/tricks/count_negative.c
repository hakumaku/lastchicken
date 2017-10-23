#include <stdio.h>

size_t count_negative(int *arr, size_t len);

int main(void)
{
	int test[9] = { 0, 1, -1, 2, -2, 5, 19, 8, -7 };

	printf("%ld\n", count_negative(test, 9));

	return 0;
}

size_t count_negative(int *arr, size_t len)
{
	size_t n = 0;
	int *end = arr+len;

	while (arr < end)
	{
		/*
		 * cmpl	$-2147483648, (%rdi)
		 *	(Compare 0 with *arr.
		 *	Also, it can be interpreted as subtract *arr - 0
		 *	in a binary way. The carry flag would be set.)
		 * sbbq	$-1, %rax
		 *	(Subtract *arr - (-1) - CF.
		 *	If CF == 1 meaning *arr is positive
		 *	resulting in *arr -1 + 1, otherwise, it would subtract -1.)
		 */
		if (*arr < 0)
		{
			n++;
		}
		arr++;
	}

	return n;
}
