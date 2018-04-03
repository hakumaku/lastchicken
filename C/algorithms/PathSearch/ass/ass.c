/*
 * A* Search(A star search)
 *
 * One of informed search algorithms that it solves
 * problems by searching among all possible paths to the solution for
 * the one that incurs the smallest cost.
 * f(n) = g(n) + h(n) where n is the last node on the path,
 * g(n) is the cost of the path from the start node to n,
 * and h(n) is a heuristic that estimates the cost of the cheapest
 * path from n to the goal.
 * Note that when g(n) = 0, it is Greedy best-first search, and
 * when h(n) = 0, dijkstra.
 */
#include "ass.h"

static List *search(MazeMat *maze, Point *end);

List *astar_search(MazeMat *maze)
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

		clearup_maze(maze);
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
				/*
				 * Addition to greedy choice,
				 * take distance from starting point
				 * into priority.
				 */
				size_t distance = point->distance + 1;
				p->distance = distance;
				size_t priority = manhattan_distance(p, end);
				prior_push(branch, p, priority + distance);

				p = look_around(maze, point);

				if (p == NULL)
				{
					break;
				}
			}

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

