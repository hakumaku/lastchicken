#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void print_path(void);
void add_pathenv(const char *value);

int main(int argc, const char *argv[])
{
	puts("Add PATH=/hi/this/is/a/test");
	add_pathenv("/hi/this/is/a/test");
	print_path();

	puts("Put PATH=/hi/this/is/test");
	putenv("PATH=/hi/this/is/test");
	print_path();

	puts("Set PATH=/hi/this/is/another/test");
	/* If true, it changes its value, otherwise it does not. */
	setenv("PATH", "/hi/this/is/another/test", true);
	print_path();

	return 0;
}

void print_path(void)
{
	char *path = getenv("PATH");
	char *ptr = path;
	char pathname[256] = { 0 };

	while (*ptr != '\0')
	{
		if (*ptr == ':')
		{
			/* One for '\0' */
			snprintf(pathname, ptr-path+1, "%s", path);
			printf("%s\n", pathname);
			path = ptr+1;
		}
		ptr++;	
	}
	snprintf(pathname, ptr-path+1, "%s", path);
	printf("%s\n", pathname);
}
void add_pathenv(const char *value)
{
	char *path = getenv("PATH");
	size_t path_len = strlen(path);
	size_t value_len = strlen(value);
	char *new_path = (char *)calloc(path_len+value_len+2, sizeof(char));

	strncpy(new_path, path, path_len);
	new_path[path_len] = ':';
	strncat(new_path, value, value_len);
	new_path[path_len+value_len+1] = '\0';

	setenv("PATH", new_path, true);

	free(new_path);
}
