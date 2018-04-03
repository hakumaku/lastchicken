// #include "ids/ids.h"
// #include "gbs/gbs.h"
#include "ass/ass.h"

int main(int argc, const char *argv[])
{
	const char *test_txt = "texts/test(windows).txt";
	/*
	if (argc != 2)
	{
		fprintf(stderr, "Command line argument missing.\n");
		exit(1);
	}
	*/

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

	// List *paths = iterative_deepening(foo);
	// List *paths = greedy_bestfirst_search(foo);
	List *paths = astar_search(foo);


	if (paths)
	{
		Node *temp = paths->head;
		for (size_t i = 0; i < paths->count; i++)
		{
			print_shortest_path(temp->data);
			write_shortest_path(foo, temp->data);
			temp = temp->next;
		}
	}
	else
	{
		fprintf(stderr, "There is no exit in the maze.\n");
	}

	free_shortest_path(paths);
	free_maze(foo);

	return 0;
}

