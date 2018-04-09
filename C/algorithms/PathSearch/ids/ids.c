/*
 * Iterative Deepening Search
 *
 * Similar to depth-first search,
 * but there is a possibility that it falls into
 * a infinite loop. To prevent it from not getting out of it,
 * it sets the maximum depth and increase it until it finds
 * the solution.
 */
#include "ids.h"

static List *search(MazeMat *maze, size_t depth, Point *start, Point *end);
/* Any exit that appears first. */
static List *nearest_search(MazeMat *maze, size_t depth, Point *start);

List *iterative_deepening(MazeMat *maze)
{
	if (maze == NULL)
	{
		return NULL;
	}

	size_t fixed_depth = maze->rows * maze->cols;
	List *solution = init_list();
	Point *start = locate_starting(maze);
	Point *end = locate_ending(maze);

	while (end)
	{
		for (size_t i = 1; i < fixed_depth; i++)
		{
			List *path = search(maze, i, start, end);

			if (path)
			{
				push(solution, path);
				break;
			}

			clearup_maze(maze);
		}

		end = locate_ending(maze);
	}

	return solution;
}

List *nearest_iterative_deepening(MazeMat *maze)
{
	if (maze == NULL)
	{
		return NULL;
	}

	size_t fixed_depth = maze->rows * maze->cols;
	List *path = NULL;
	Point *start = locate_starting(maze);

	for (size_t i = 1; i < fixed_depth; i++)
	{
		path = nearest_search(maze, i, start);

		if (path)
		{
			break;
		}

		clearup_maze(maze);
	}

	return path;
}

static List *search(MazeMat *maze, size_t depth, Point *start, Point *end)
{
	List *path = NULL;
	List *branch = init_list();
	size_t movement = 0;

	/*
	 * Put the current node into 'path', and
	 * look around all ROADs, up, right, down and left.
	 * 1) Only two ROADs.
	 *	one must be the previous node,
	 *	the other the next node to go.
	 *	Move on to the next node.
	 * 2) More than two.
	 *	Put all nodes except the previous one into 'branch'.
	 *	Move on to an arbitrarily chosen one.
	 * 3) No ROAD.
	 *	If 'branch' non-empty:
	 *		Pop enough nodes from 'path'.
	 *		Start it from the node popped from 'branch'.
	 *	Else:
	 *		No exit exists.
	 */
	Point *point = start;

	for (size_t i = 0; i < depth; i++)
	{
		/* Found an exit. */
		if (point == end)
		{
			break;
		}

		/* Get next point. */
		Point *p = look_around(maze, point);

		/* Push next point. */
		if (p)
		{
			point = p;
			point->eval = true;
			movement++;

			/*
			 * If it has more than one,
			 * push them into 'branch'.
			 */
			while (true)
			{
				p = look_around(maze, point);

				if (p == NULL)
				{
					break;
				}

				push(branch, p);
			}
		}
		/* Dead end */
		else
		{
			Point *branching = dequeue(branch);

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

	free_list(branch);

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

static List *nearest_search(MazeMat *maze, size_t depth, Point *start)
{
	List *path = NULL;
	List *branch = init_list();
	size_t movement = 0;

	/*
	 * Put the current node into 'path', and
	 * look around all ROADs, up, right, down and left.
	 * 1) Only two ROADs.
	 *	one must be the previous node,
	 *	the other the next node to go.
	 *	Move on to the next node.
	 * 2) More than two.
	 *	Put all nodes except the previous one into 'branch'.
	 *	Move on to an arbitrarily chosen one.
	 * 3) No ROAD.
	 *	If 'branch' non-empty:
	 *		Pop enough nodes from 'path'.
	 *		Start it from the node popped from 'branch'.
	 *	Else:
	 *		No exit exists.
	 */
	Point *point = start;

	for (size_t i = 0; i < depth; i++)
	{
		/* Found an exit. */
		if (point->kind == ENDING_POINT)
		{
			break;
		}

		/* Get next point. */
		Point *p = look_around(maze, point);

		/* Push next point. */
		if (p)
		{
			point = p;
			point->eval = true;
			movement++;

			/*
			 * If it has more than one,
			 * push them into 'branch'.
			 */
			while (true)
			{
				p = look_around(maze, point);

				if (p == NULL)
				{
					break;
				}

				push(branch, p);
			}
		}
		/* Dead end */
		else
		{
			Point *branching = dequeue(branch);

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
	free_list(branch);

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

