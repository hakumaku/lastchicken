#include <stdio.h>

int main(void)
{
	int ch = 0;
	char buf[100] = { 0 };

	// setvbuf(stdout, buf, _IOFBF, 100);
	setvbuf(stdout, buf, _IONBF, 100);
	// setvbuf(stdout, buf, _IOLBF, 100);
	while ((ch = getchar()) != '#')
		putchar(ch);

	return 0;
}
