/*
 * Try executing ./a.out several times.
 * The outcome can be sometimes different.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUF_SIZE 32

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		puts("File name should be passed.");
		exit(1);
	}

	int fd = 0;
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		puts("Opening the file has failed.");
		exit(2);
	}

	unsigned char buf[BUF_SIZE] = { 0 };
	ssize_t nbytes = 0;
	off_t pos = lseek(fd, 0, SEEK_CUR);

	pid_t pid = 0;

	printf("Before forking current cursor position: %ld\n\n", pos);

	if ((pid = fork()) < 0)
	{
		puts("Error has occured.");
		exit(1);
	}
	if ((nbytes = read(fd, buf, sizeof(buf)-1)) < 0)
	{
		puts("Reading the file has failed.");
		exit(3);
	}

	if (pid == 0)
	{
		pos = lseek(fd, 0, SEEK_CUR);
		puts("I am a child:");
		printf("Current cursor position: %ld\n\n", pos);
	}
	else
	{
		pos = lseek(fd, 0, SEEK_CUR);
		puts("I am a parent:");
		printf("Current cursor position: %ld\n\n", pos);
	}

	return 0;
}

