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
#include "maze_mat.h"
#include "my_list.h"

static List *depth_first_search(MazeMat *maze, size_t depth);

List *iterative_deepening(MazeMat *maze)
{
	size_t fixed_depth = maze->rows * maze->cols;
	List *solution = init_list();

	for (size_t i = 1; i < fixed_depth; i++)
	{
		List *path = depth_first_search(maze, i);

		if (path)
		{
			push(solution, path);
		}
	}

	return solution;
}

static List *depth_first_search(MazeMat *maze, size_t depth)
{
	/* Stack */
	List *path = init_list();
	/* Queue */
	List *branch = init_list();
	bool found = false;

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
	Point *point = locate_starting(maze);
	push(path, point);

	for (size_t i = 0; i < depth; i++)
	{
		/* Current point. */
		point = path->head->data;

		/* Found an exit. */
		if (point->kind == ENDING_POINT && point->eval == false)
		{
			push(path, point);
			point->eval = true;
			found = true;
			break;
		}

		/* Get next point. */
		Point *p = look_around(maze, point);

		/* Push next point. */
		if (p)
		{
			push(path, p);

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
				/* Error handling */
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
					}
				}

				push(path, branching);
			}
		}
	}

	/* Deallocate the rest. */
	while (branch->head)
	{
		pop(branch);
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

	return path;
}

