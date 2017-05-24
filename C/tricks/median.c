#include <stdio.h>

int median(int a, int b, int c);
int largest(int a, int b, int c);

int main(void)
{
	int a = 10, b = 3, c = 21;
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

	if(median < b)
		median = b;
	if(median > c)
	{
		median = a ^ b ^ median;
		if(median < c)
			median = c;
	}

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
