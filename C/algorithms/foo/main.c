#include "ids/ids.h"

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Command line argument missing.\n");
		exit(1);
	}

	printf("Reading file(%s)...\n", argv[1]);
	MazeMat *foo = init_maze(argv[1]);

	if (foo == NULL)
	{
		fprintf(stderr, "Opening file has failed.\n");
		exit(1);
	}
	print_maze(foo);

	Point *s = locate_starting(foo);

	if (s)
	{
		printf("s: (%ld, %ld)\n", s->x, s->y);
		free(s);
	}

	while (true)
	{
		Point *e = locate_ending(foo);

		if (e == NULL)
		{
			break;
		}

		printf("e: (%ld, %ld)\n", e->x, e->y);
		free(e);
	}

	List *path = iterative_deepening(foo);
	print_shortest_path(path);

	free_maze(foo);

	return 0;
}

