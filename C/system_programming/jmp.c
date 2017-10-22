/*
 * Nonlocal goto.
 * Useful for handling error conditions
 * in a deeply nested function call.
 *
 * Compare the following:
 * gcc -O jmp.c
 * gcc jmp.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static jmp_buf mark;

void test_func();

int main(void)
{
	static int called = 1;
	volatile int volatileVal = 10;
	auto int autoVal = 10;

	int value = setjmp(mark);

	printf("Line 18 reached: %d\n\n", called++);
	if (value)
	{
		printf("After jumping...\nlocal = %d\nvolatileVal = %d\n\n", autoVal, volatileVal);
		exit(value);
	}
	else
	{
		autoVal = 20;
		volatileVal = 20;
		printf("Before jumping...\nautoVal = %d\nvolatileVal = %d\n\n", autoVal, volatileVal);
		test_func();
	}


	return 0;
}

void test_func()
{
	static int stack = 0;
	if (stack++ < 5)
	{
		test_func();
	}
	else
	{
		longjmp(mark, 1);
	}
	printf("Line 44 will not be reached.\n");
}

