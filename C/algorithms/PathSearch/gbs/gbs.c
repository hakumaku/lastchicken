/*
 * Greedy best-first search
 * Unlike iterative deepening search,
 * it chooses one 'greedily' each time it meets a branching point.
 */
#include "gbs.h"

static List *search(MazeMat *maze, Point *start, Point *end);

List *greedy_bestfirst_search(MazeMat *maze)
{
	List *solution = init_list();
	Point *start = locate_starting(maze);
	Point *end = locate_ending(maze);

	while (end)
	{
		List *path = search(maze, start, end);

		if (path)
		{
			push(solution, path);
		}

		end = locate_ending(maze);
	}

	return solution;
}

static List *search(MazeMat *maze, Point *start, Point *end)
{
	List *path = NULL;
	PriorList *branch = init_prior_list();
	size_t movement = 0;
	Point *point = start;

	while (point != end)
	{
		Point *p = look_around(maze, point);

		if (p)
		{
			while (true)
			{
				/* "Greedily" push. */
				size_t priority = manhattan_distance(p, end);
				prior_push(branch, p, priority);

				p = look_around(maze, point);

				if (p == NULL)
				{
					break;
				}
			}

			/* "Greedily" choose. */
			point = prior_pop(branch);
			point->eval = true;
			movement++;

			continue;
		}
		else
		{
			Point *branching = prior_pop(branch);

			/* No exit in maze. */
			if (branching == NULL)
			{
				break;
			}
			else
			{
				point = branching;
				point->eval = true;
				movement++;
			}
		}
	}

	/* Deallocate the rest. */
	while (branch->head)
	{
		prior_pop(branch);
	}
	free(branch);

	/* Returns NULL when it didn't find one. */
	if (point == end)
	{
		path = construct_path(maze, end);

		/* Starting point and exiting point does not count. */
		PathInfo *info = create_info(path->count-2, movement);
		push(path, info);
	}

	return path;
}

