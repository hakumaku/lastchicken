#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int **ptr = (int **)calloc(3, sizeof(int *));
	int **pptr = ptr;
	int x = 1;
	int y = 2;
	int z = 3;
	int *a = &x;
	int *b = &y;
	int *c = &z;

	*pptr++ = a;
	*pptr++ = b;
	*pptr++ = c;

	printf("ptr[0]: %d, ptr[1]: %d, ptr[2]: %d\n", *ptr[0], *ptr[1], *ptr[2]);

	return 0;
}

