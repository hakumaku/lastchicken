#include <stdio.h>
#include <stdarg.h>

void foo(int arg, ...);

int main(int argc, const char *argv[])
{
	foo(1, 2, 3, 4, -1);

	return 0;
}

void foo(int arg, ...)
{
	int bar = 0;
	va_list ap;

	va_start(ap, arg);
	while ((bar = va_arg(ap, int)) != -1)
	{
		printf("bar: %d\n", bar);
	}
	va_end(ap);
}

