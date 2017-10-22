/*
 * Try executing ./a.out several times.
 * The outcome can be sometimes different.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void print_id(void);

int main(int argc, const char *argv[])
{
	pid_t pid = 0;
	int val = 10;

	printf("Before forking: %d\n\n", val);

	pid = fork();
	if (pid == 0)
	{
		/*
		 * Since modern implementation
		 * uses a strategy of COW(copy-on-write),
		 * 'val' is copied at this moment
		 * when the child tries to write.
		 */
		puts("I am a child:");
		print_id();
		val++;
		printf("Child has increased val: %d\n\n", val);
	}
	else if (pid > 0)
	{
		puts("I am a parent:");
		print_id();
		val++;
		printf("Parent has increased val: %d\n\n", val);
	}
	else // pid < 0
	{
		puts("Error has occured.");
		exit(1);
	}

	printf("After forking: %d\n\n", val);

	return 0;
}

void print_id(void)
{
	printf("%4s %d (%14s %d)\n",
			"PID:", getpid(), "Parent's PID:", getppid());
	printf("%4s %d (%s %d)\n",
			"UID:", getuid(), "Effective UID:", geteuid());
	printf("%4s %d (%s %d)\n",
			"GID:", getgid(), "Effective GID:", getegid());
}

