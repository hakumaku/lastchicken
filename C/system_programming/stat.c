#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
/*
 * int stat(const char *pathname, struct stat *buf)
 * int fstat(int filedes, struct stat *buf)
 * int lstat(const char *pathname, struct *buf)
 */
void print_stat(struct stat *buf);

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

	/* Using path */
	struct stat buf = {};
	if (stat(argv[1], &buf) == -1)
	{
		puts("Reading stat has failed.");
		exit(3);
	}

	puts("stat:");
	print_stat(&buf);
	putchar('\n');

	/* Using file descriptor */
	struct stat fbuf = {};
	if (fstat(fd, &fbuf) == -1)
	{
		puts("Reading fstat has failed.");
		exit(4);
	}

	puts("fstat:");
	print_stat(&fbuf);
	putchar('\n');

	struct stat lbuf = {};
	if (lstat(argv[1], &lbuf) == -1)
	{
		puts("Reading lstat has failed.");
		exit(5);
	}

	puts("lstat:");
	print_stat(&lbuf);

	close(fd);

	return 0;
}

void print_stat(struct stat *buf)
{
	mode_t mode = buf->st_mode;
	char perm[10] = { 0 };
	char *type = NULL;
	perm[0] = mode & S_IXUSR ? 'x' : '-';
	perm[1] = mode & S_IWUSR ? 'w' : '-';
	perm[2] = mode & S_IRUSR ? 'r' : '-';
	perm[3] = mode & S_IXGRP ? 'x' : '-';
	perm[4] = mode & S_IWGRP ? 'w' : '-';
	perm[5] = mode & S_IRGRP ? 'r' : '-';
	perm[6] = mode & S_IXOTH ? 'x' : '-';
	perm[7] = mode & S_IWOTH ? 'w' : '-';
	perm[8] = mode & S_IROTH ? 'r' : '-';

	if (S_ISREG(buf->st_mode))
	{
		type = "Regular";
	}
	else if (S_ISDIR(buf->st_mode))
	{
		type = "Directory";
	}
	else if (S_ISCHR(buf->st_mode))
	{
		type = "Character";
	}
	else if (S_ISBLK(buf->st_mode))
	{
		type = "Block";
	}
	else if (S_ISFIFO(buf->st_mode))
	{
		type = "Fifo";
	}
	else if (S_ISLNK(buf->st_mode))
	{
		type = "Link";
	}
	else if (S_ISSOCK(buf->st_mode))
	{
		type = "Socket";
	}
	else
	{
		type = "Unknown";
	}

	printf("%9s %s\n", "Mode:", perm);
	printf("%9s %lu\n", "Inode:", buf->st_ino);
	printf("%9s %lu\t%9s %lu\n",
			"Dev:", buf->st_dev, "Rdev:", buf->st_rdev);
	printf("%9s %lu\n", "Links:", buf->st_nlink);
	printf("%9s %d\t%9s %d\n",
			"UID:", buf->st_uid, "GID:", buf->st_gid);
	printf("%9s %s\n", "Type:", type);
	printf("%9s %lu\t(%9s %lu %9s %lu)\n",
			"Size:", buf->st_size,
			"IO Block:", buf->st_blksize, "Blocks:", buf->st_blocks);
	printf("%9s %s", "Access:", ctime(&buf->st_atime));
	printf("%9s %s", "Modify:", ctime(&buf->st_mtime));
	printf("%9s %s", "Change:", ctime(&buf->st_ctime));
}
