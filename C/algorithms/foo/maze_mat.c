#include "maze_mat.h"
#include "my_list.h"

#define IS_DIGIT(c)		(c > 47 && c < 58)
#define TO_DIGIT(c)		(c - '0')

/* Most of MazeMat functions are declared public. */
static MazeMat *create_mat(size_t m, size_t n);

/* The following two function are not used. */
static size_t count_number(String *line);
static size_t count_lines(FILE *fp);
/********************************************/

/* Functions related to Point. */
static Point *create_point(size_t i, size_t j, MazeKind kind, MazePrev prev);
static Point *locate_single_point(MazeMat *src, size_t from_i, size_t from_j, MazeKind point);
static Point *locate_multiple_point(MazeMat *src, MazeKind point);

static MazeMat *create_mat(size_t m, size_t n)
{
	MazeMat *mat = (MazeMat *)calloc(1, sizeof(MazeMat));
	mat->rows = m;
	mat->cols = n;
	mat->data = (Point *)calloc(m*n, sizeof(Point));

	Point *data = mat->data;
	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			data->x = i;
			data->y = j;
		}
	}

	return mat;
}

void free_maze(MazeMat *src)
{
	if (src)
	{
		free(src->data);
		free(src);
	}
}

void print_maze(MazeMat *src)
{
	size_t m = src->rows;
	size_t n = src->cols;
	Point *data = src->data;

	printf("MazeMat(%ld x %ld)\n", m, n);
	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			printf("%d ", data->kind);
			data++;
		}
		putchar('\n');
	}
}

/*
 * Returns a matrix created by reading text file.
 */
MazeMat *init_maze(const char *text_file)
{
	FILE *fp = fopen(text_file, "r");

	if (fp == NULL)
	{
		return NULL;
	}

	String *line = read_ltos(fp);
	size_t col = 0;
	size_t row = 0;

	if (sscanf(line->text, "%lu %lu", &row, &col) != 2)
	{
		fprintf(stderr, "Could not read 'm' and 'n' in the first line.\n");

		free(line);
		fclose(fp);

		return NULL;
	}

	MazeMat *mat = create_mat(row, col);
	Point *data = mat->data;

	/* Frees the first line of text file. */
	free(line);

	while (true)
	{
		line = read_ltos(fp);

		if (line == NULL)
		{
			break;
		}

		size_t len = line->len;
		char *text = line->text;

		for (size_t i = 0; i < len; i++)
		{
			if (IS_DIGIT(*text))
			{
				data->kind = TO_DIGIT(*text);
				data++;
			}
			text++;
		}

		free(line);
	}

	fclose(fp);

	return mat;
}

void print_shortest_path(List *paths)
{
	if (paths == NULL || paths->count == 0)
	{
		return;
	}

	while (true)
	{
		List *path = pop(paths);

		if (path == NULL)
		{
			break;
		}

		Point *node = NULL;

		while (path->count > 1)
		{
			node = dequeue(path);
			printf("(%ld, %ld) -> ", node->x, node->y);
		}

		node = dequeue(path);
		printf("(%ld, %ld)\n", node->x, node->y);
	}
}

/*
 * Returns the number of digits in a String.
 */
static size_t count_number(String *line)
{
	size_t count = 0;
	size_t len = line->len;
	char *text = line->text;

	for (size_t i = 0; i < len; i++)
	{
		if (IS_DIGIT(*text))
		{
			count++;
		}

		text++;
	}

	return count;
}

/*
 * Returns the number of lines in FILE.
 */
static size_t count_lines(FILE *fp)
{
	if (fp == NULL)
	{
		return 0;
	}

	int ch = 0;
	size_t count = 1;
	long pos = ftell(fp);

	fseek(fp, 0, SEEK_SET);

	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
		{
			count++;
		}
	}

	fseek(fp, pos, SEEK_SET);

	return count;
}

/********************
 * Points functions *
 ********************/
static Point *create_point(size_t i, size_t j, MazeKind kind, MazePrev prev)
{
	Point *point = (Point *)calloc(1, sizeof(Point));
	point->x = i;
	point->y = j;
	point->kind = kind;
	point->from = prev;

	return point;
}

/* Wrapper of finding out STARTING_POINT */
Point *locate_starting(MazeMat *src)
{
	return locate_single_point(src, 0, 0, STARTING_POINT);
}

/* Wrapper of finding out ENDING_POINT */
Point *locate_ending(MazeMat *src)
{
	return locate_multiple_point(src, ENDING_POINT);
}

static Point *locate_single_point(MazeMat *src, size_t from_i, size_t from_j, MazeKind kind)
{
	size_t n = src->cols;
	size_t i = from_j == n ? from_i + 1 : from_i;
	size_t j = from_j == n ? 0 : from_j;
	Point *data = src->data + i * n + j;
	Point *end = data + src->rows * n;

	while (data < end)
	{
		if (data->kind == kind)
		{
			break;
		}

		data++;
		j++;

		i += (j == n);
		j = (j == n) ? 0 : j;
	}

	if (data == end)
	{
		// fprintf(stderr, "There is no %d in the matrix.\n", point);
		return NULL;
	}

	return create_point(i, j, kind, NONE);
}

static Point *locate_multiple_point(MazeMat *src, MazeKind kind)
{
	static List *points = NULL;
	static bool init = false;

	if (init)
	{
		Point *s = dequeue(points);

		if (s == NULL)
		{
			init = false;
			free(points);
		}

		return s;
	}
	else
	{
		init = true;

		points = init_list();

		size_t i = 0;
		size_t j = 0;

		while (true)
		{
			Point *p = locate_single_point(src, i, j, kind);

			if (p == NULL)
			{
				break;
			}

			i = p->x;
			j = p->y+1;

			enqueue(points, p);
		}

		return dequeue(points);
	}
}

/*
 * Look around four directions of the given point.
 * Each time it is invoked, it returns a point.
 */
Point *look_around(MazeMat *src, Point *p)
{
	static List *direction = NULL;

	if (direction == NULL)
	{
		size_t i = p->x;
		size_t j = p->y;
		size_t from = p->from;

		direction = init_list();

		/* Up */
		if (i != 0 && from != UP)
		{
			Point *up = p - src->cols;

			if (up->eval == false && up->kind != WALL)
			{
				up->from = DOWN;
				enqueue(direction, up);
			}
		}

		/* Right */
		if (j != src->cols-1 && from != RIGHT)
		{
			Point *right = p + 1;

			if (right->eval == false && right->kind != WALL)
			{
				right->from = LEFT;
				enqueue(direction, right);
			}
		}

		/* Down */
		if (i != src->rows-1 && from != DOWN)
		{
			Point *down = p + src->cols;

			if (down->eval == false && down->kind != WALL)
			{
				down->from = UP;
				enqueue(direction, down);
			}
		}

		/* Left */
		if (j != 0 && from != LEFT)
		{
			Point *left = p - 1;

			if (left->eval == false && left->kind != WALL)
			{
				left->from = RIGHT;
				enqueue(direction, left);
			}
		}
	}

	if (direction->count)
	{
		return dequeue(direction);
	}
	else
	{
		free(direction);
		direction = NULL;

		return NULL;
	}
}

Point *get_previous_point(MazeMat *maze, Point *p)
{
	if (p == NULL)
	{
		return NULL;
	}

	MazePrev from = p->from;
	Point *prev = NULL;
	size_t stride = maze->rows;

	if (from == UP)
	{
		prev = p - stride;
	}
	else if (from == RIGHT)
	{
		prev = p + 1;
	}
	else if (from == DOWN)
	{
		prev = p + stride;
	}
	else
	{
		prev = p - 1;
	}

	return prev;
}

