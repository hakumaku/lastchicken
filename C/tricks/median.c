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
	int v1 = a;
	int v2 = a ^ b;

	v1 = v1 < b ? b : v1;
	v2 ^= v1;

	v1 = c < v1 ? c : v1;

	return v1 < v2 ? v2 : v1;
}
int largest(int a, int b, int c)
{
	int largest = a;

	largest = largest < b ? b : largest;
	largest = largest < c ? c : largest;

	return largest;
}
