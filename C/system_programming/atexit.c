#include <stdio.h>
#include <stdlib.h>

void f1(void) { printf("f1\n"); };
void f2(void) { printf("f2\n"); };
void f3(void) { printf("f3\n"); };

int main(void)
{
	printf("Start\n");
	atexit(f3);
	atexit(f1);
	atexit(f2);
	atexit(f2);
	atexit(f1);
	printf("Done\n");

	return 0;
}
