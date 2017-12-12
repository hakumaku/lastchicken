#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		puts("Command-line argument required.");
		exit(0);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		puts("Opening file has failed.");
		exit(1);
	}

	/* Opening flags matter when using mmap. */
	int new_fd = open("new.txt", O_RDWR|O_CREAT|O_TRUNC, 0664);
	if (new_fd < 0)
	{
		puts("Creating a new file has failed.");
		exit(2);
	}

	struct stat info = { 0 };
	void *dst = NULL;
	void *src = NULL;

	if (fstat(fd, &info) == -1)
	{
		puts("Getting file information has failed.");
		exit(3);
	}

	if (ftruncate(new_fd, info.st_size) < 0)
	{
		puts("Truncating file has failed.");
		exit(4);
	}

	src = mmap(NULL, info.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (src == MAP_FAILED)
	{
		puts("src mapping has failed.");
		exit(5);
	}
	dst = mmap(NULL, info.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, new_fd, 0);
	if (dst == MAP_FAILED)
	{
		puts("dst mapping has failed.");
		exit(6);
	}

	memcpy(dst, src, info.st_size);

	/* munmap is like free(), malloc <-> free */
	munmap(src, info.st_size);
	munmap(dst, info.st_size);

	close(fd);
	close(new_fd);

	return 0;
}

