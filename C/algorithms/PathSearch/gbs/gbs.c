/*
 * Greedy best-first search
 * Unlike iterative deepening search,
 * it chooses one 'greedily' each time it meets a branching point.
 */
#include "gbs.h"

static List *search(MazeMat *maze, Point *start, Point *end);
/* Any exit that appears first. */
static List *nearest_search(MazeMat *maze, Point *start, List *ends);

List *greedy_bestfirst_search(MazeMat *maze)
{
	if (maze == NULL)
	{
		return NULL;
	}

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

List *greedy_bestfirst_nearest_search(MazeMat *maze)
{
	if (maze == NULL)
	{
		return NULL;
	}

	List *path = NULL;
	List *ends = init_list();
	Point *start = locate_starting(maze);
	Point *end = locate_ending(maze);

	while (end)
	{
		push(ends, end);

		end = locate_ending(maze);
	}

	path = nearest_search(maze, start, ends);

	free_list(ends);

	return path;
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

	free_prior_list(branch);

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

static List *nearest_search(MazeMat *maze, Point *start, List *ends)
{
	List *path = NULL;
	PriorList *branch = init_prior_list();
	size_t movement = 0;
	Point *point = start;

	while (point->kind != ENDING_POINT)
	{
		Point *p = look_around(maze, point);

		if (p)
		{
			size_t distance = point->distance + 1;

			while (true)
			{
				/*
				 * Addition to greedy choice,
				 * take distance from starting point
				 * into priority.
				 */
				p->distance = distance;
				size_t priority = nearest_manhattan_distance(p, ends);
				prior_push(branch, p, priority + distance);

				p = look_around(maze, point);

				if (p == NULL)
				{
					break;
				}
			}

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
			}
				movement++;
		}
	}

	/* Deallocate the rest. */
	free_prior_list(branch);

	/* Returns NULL when it didn't find one. */
	if (point->kind == ENDING_POINT)
	{
		path = construct_path(maze, point);

		/* Starting point and exiting point does not count. */
		PathInfo *info = create_info(path->count-2, movement);
		push(path, info);
	}

	return path;
}

