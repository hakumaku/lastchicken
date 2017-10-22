#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		puts("File name should be passed.");
		exit(1);
	}

	/* Returns 0 on success. */
	int rperm = access(argv[1], R_OK);
	int wperm = access(argv[1], W_OK);
	int xperm = access(argv[1], X_OK);
	/* Test for the existence of the file. */
	int fexist = access(argv[1], F_OK);

	printf("Read? %d, Write? %d, Execute? %d, Exist? %d\n",
			rperm, wperm, xperm, fexist);

	return 0;
}
