/*
 * Imperative Style & Functional Style
 *
 * It is not always best to implement a function
 * in a functional style which takes advantage of 
 * conditional move(CS:APP pg587),
 * but whenever it seems feasible,
 * better implement in a functional style.
 */
#include <stdio.h>

/*	Imperative	*/
void minmax1(int a[], int b[], size_t n);

/*	Functional	*/
void minmax2(int a[], int b[], size_t n);

int main()
{
	int test1a[] = {11,12,13,14,15,16,17,18,19,20};
	int test1b[] = {1,2,3,4,5,6,7,8,9,10};
	int test2a[] = {11,12,13,14,15,16,17,18,19,20};
	int test2b[] = {1,2,3,4,5,6,7,8,9,10};
	size_t len = sizeof(test1a) / sizeof(int);

	minmax1(test1a, test1b, len);
	minmax2(test2a, test2b, len);

	printf("test1a: ");
	for(int i = 0; i < len; i++)
		printf("%.2d ", test1a[i]);
	putchar('\n');
	printf("test1b: ");
	for(int i = 0; i < len; i++)
		printf("%.2d ", test1b[i]);
	putchar('\n');
	puts("=====================================");
	printf("test1a: ");
	for(int i = 0; i < len; i++)
		printf("%.2d ", test2a[i]);
	putchar('\n');
	printf("test1b: ");
	for(int i = 0; i < len; i++)
		printf("%.2d ", test2b[i]);
	putchar('\n');

	return 0;
}
/*
 * Imperative Style
 * Rearrange two vectors so that for each i, b[i] >= a[i]
 */
void minmax1(int a[], int b[], size_t n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		if(a[i] > b[i])
		{
			int t = a[i];
			a[i] = b[i];
			b[i] = t;
		}
	}
}
/*
 * Functional Style
 * Rearrange two vectors so that for each i, b[i] >= a[i]
 */
void minmax2(int a[], int b[], size_t n)
{
	int i;
	for(i = 0; i < n; i++)
	{
		int min = a[i] < b[i] ? a[i] : b[i];
		int max = a[i] < b[i] ? b[i] : a[i];
		a[i] = min;
		b[i] = max;
	}
}