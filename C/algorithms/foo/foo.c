#include <stdio.h>

int main(int argc, const char *argv[])
{
	FILE *fp = fopen("asdf.txt", "r");

	if (fp == NULL)
	{
		printf("It failed.\n");
	}
	else
	{
		puts("It opened.");
	}

	return 0;
}


