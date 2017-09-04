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
/*
 * Strategy: find out which argument is the largest,
 * and exclude it. After that return the larger of
 * the rest two.
 */
int median(int a, int b, int c)
{
	int median = a;
	int min = a ^ b;

	/* max(a,b) */
	if(median < b)
		median = b;
	min ^= median;

	/* min(max(a,b), c) */
	if(c < median)
		median = c;

	/* max(min, min(max(a,b), c)) */
	if(median < min)
		median = min;

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
