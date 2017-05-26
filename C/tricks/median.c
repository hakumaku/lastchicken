#include <stdio.h>

int median(int a, int b, int c);
int largest(int a, int b, int c);

int main(void)
{
	int a = 5, b = 9, c = 13;
	printf("a:%d b:%d c:%d\n", a, b, c);
	printf("largest:%d\n", largest(a,b,c));
	printf("largest:%d\n", largest(a,c,b));
	printf("largest:%d\n", largest(b,a,c));
	printf("largest:%d\n", largest(b,c,a));
	printf("largest:%d\n", largest(c,a,b));
	printf("largest:%d\n", largest(c,b,a));

	printf("median:%d\n", median(a,b,c));
	printf("median:%d\n", median(a,c,b));
	printf("median:%d\n", median(b,a,c));
	printf("median:%d\n", median(b,c,a));
	printf("median:%d\n", median(c,a,b));
	printf("median:%d\n", median(c,b,a));

	return 0;
}

int median(int a, int b, int c)
{
	int median = a;
	int median2 = a ^ b;

	/*
	 * 1) median = a, median2 = b
	 * 2) median = b, median2 = a
	 */
	if(median < b)
		median = b;
	median2 ^= median;

	/*
	 * 1) median = a, median2 = max(b,c)
	 * 2) median = b, median2 = max(a,c)
	 */
	if(median2 < c)
		median2 = c;

	/*
	 * median2 < median ? <-> is median the largest?
	 * then, select median2 which is either max(b,c) or max(a,c).
	 */
	if(median2 < median)
		median = median2;

	return median;
}
int largest(int a, int b, int c)
{
	int largest = a;

	if(largest < b)
		largest = b;
	if(largest < c)
		largest = c;

	return largest;
}
