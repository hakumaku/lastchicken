/*
 * Greedy best-first search
 * Unlike iterative deepening search,
 * it chooses one 'greedily' each time it meets a branching point.
 */
#include "gbs.h"

static size_t manhattan_distance(Point *s, Point *d);
static List *search(MazeMat *maze, Point *end);

List *greedy_bestfirst_search(MazeMat *maze)
{
	List *solution = init_list();
	Point *end = locate_ending(maze);

	while (end)
	{
		List *path = search(maze, end);

		if (path)
		{
			push(solution, path);
		}

		end = locate_ending(maze);
	}

	return solution;
}

static List *search(MazeMat *maze, Point *end)
{
	List *path = init_list();
	PriorList *branch = init_prior_list();
	bool found = false;
	size_t movement = 0;

	Point *point = locate_starting(maze);
	push(path, point);

	while (true)
	{
		point = path->head->data;

		if (point == end)
		{
			point->eval = true;
			found = true;
			break;
		}

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
			p = prior_pop(branch);

			push(path, p);
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
				Point *threshold = get_previous_point(maze, branching);

				/* Pop enough nodes. */
				while (true)
				{
					Point *back = path->head->data;

					if (back == threshold)
					{
						break;
					}
					else
					{
						/* Throw it away. */
						pop(path);
						movement++;
					}
				}

				push(path, branching);
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
	if (found == false)
	{
		while (path->head)
		{
			pop(path);
		}

		free(path);

		path = NULL;
	}
	else
	{
		/* Starting point and exiting point does not count. */
		PathInfo *info = create_info(path->count-2, movement);
		push(path, info);
	}

	return path;
}

static size_t manhattan_distance(Point *s, Point *d)
{
	size_t x1 = s->x;
	size_t x2 = d->x;

	size_t y1 = s->y;
	size_t y2 = d->y;

	size_t d1 = x1 > x2 ? x1 - x2 : x2 - x1;
	size_t d2 = y1 > y2 ? y1 - y2 : y2 - y1;

	return d1 + d2;
}

