#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE	32

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		puts("File name should be passed.");
		exit(1);
	}

	int fd = 0;
	if ((fd = open(argv[1], O_RDWR)) < 0)
	{
		puts("Opening the file has failed.");
		exit(2);
	}

	unsigned char buf[BUF_SIZE] = { 0 };
	ssize_t nbytes = 0;
	off_t pos = lseek(fd, 0, SEEK_CUR);

	printf("(open)Current cursor position: %ld\n\n", pos);

	if ((nbytes = read(fd, buf, sizeof(buf)-1)) < 0)
	{
		puts("Reading the file has failed.");
		exit(3);
	}

	printf("Read %ld bytes:\n", nbytes);
	printf("%s\n", buf);
	pos = lseek(fd, 0, SEEK_CUR);
	printf("(read)Current cursor position: %ld\n\n", pos);

	if ((nbytes = write(fd, buf, nbytes)) < 0)
	{
		puts("Writing the file has failed.");
		exit(4);
	}

	printf("Write %ld bytes:\n", nbytes);
	printf("%s\n", buf);
	pos = lseek(fd, 0, SEEK_CUR);
	printf("(write)Current cursor position: %ld\n\n", pos);

	close(fd);

	return 0;
}
