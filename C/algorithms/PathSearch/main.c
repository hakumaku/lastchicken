#include "ids/ids.h"
#include "gbs/gbs.h"
#include "ass/ass.h"

int main(int argc, const char *argv[])
{
	// const char *test_txt = "texts/test(windows).txt";
	const char *test_txt = argv[1];

	if (argc != 2 || test_txt == NULL)
	{
		fprintf(stderr, "Command line argument missing.\n");
		exit(1);
	}

	printf("Reading file(%s)...\n", test_txt);
	MazeMat *foo = init_maze(test_txt);

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
	}

	while (true)
	{
		Point *e = locate_ending(foo);

		if (e == NULL)
		{
			break;
		}

		printf("e: (%ld, %ld)\n", e->x, e->y);
	}

	List *path = nearest_iterative_deepening(foo);
	// List *path = greedy_bestfirst_nearest_search(foo);
	// List *path = astar_nearest_search(foo);

	if (path)
	{
		print_shortest_path(path);
		write_shortest_path(foo, path);
	}
	else
	{
		fprintf(stderr, "There is no exit in the maze.\n");
	}

	free_shortest_path(path);
	free_maze(foo);

	return 0;
}

