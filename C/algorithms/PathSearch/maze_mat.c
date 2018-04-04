#include "maze_mat.h"
#include "my_list.h"

#define IS_DIGIT(c)		(c > 47 && c < 58)
#define TO_DIGIT(c)		(c - '0')
#define TO_CHAR(d)		(d + '0')

/* Most of MazeMat functions are declared public. */
static MazeMat *create_mat(size_t m, size_t n);

/* The following two function are not used. */
static size_t count_number(String *line);
static size_t count_lines(FILE *fp);
/********************************************/

/* Functions related to Point. */
static Point *locate_single_point(MazeMat *src, size_t from_i, size_t from_j, MazeKind point);
static Point *locate_multiple_point(MazeMat *src, MazeKind point);
static Point *deep_copy_points(MazeMat *src);
static void replace_points(Point *data, size_t stride, List *path);

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

/* It clears 'distance' of all points */
void clearup_maze(MazeMat *src)
{
	Point *data = src->data;
	Point *end = data + src->cols * src->rows;

	while (data < end)
	{
		data->eval = false;
		data->distance = 0;
		data++;
	}
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
			printf("%d(%ld,%ld) ", data->kind, data->x, data->y);
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
	size_t x = 0;
	size_t y = 0;

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
				/* Initialize a point. */
				data->x = x;
				data->y = y;
				data->kind = TO_DIGIT(*text);
				data->eval = false;
				data->from = NONE;
				data->distance = 0;

				y++;
				x += (y == col);
				y = (y == col) ? 0 : y;

				data++;
			}
			text++;
		}

		free(line);
	}

	fclose(fp);

	return mat;
}

List *construct_path(MazeMat *maze, Point *end)
{
	List *path = init_list();
	Point *cur = end;

	while (cur->kind != STARTING_POINT)
	{
		push(path, cur);
		cur = get_previous_point(maze, cur);
	}
	push(path, cur);

	return path;
}

/* A signle path must be cast. */
void print_shortest_path(List *path)
{
	if (path == NULL || path->count == 0)
	{
		return;
	}

	PathInfo *info = path->head->data;
	printf("Length: %ld\n", info->length);
	printf("Time: %ld\n", info->movement);

	Node *node = path->tail;
	Point *p = NULL;
	/* Exclude the first node. */
	size_t len = path->count - 2;

	for (size_t i = 0; i < len; i++)
	{
		p = node->data;
		printf("(%ld, %ld) -> ", p->x, p->y);

		node = node->prev;
	}
	p = node->data;
	printf("(%ld, %ld)\n", p->x, p->y);
}

/* A signle path must be cast. */
void write_shortest_path(MazeMat *maze, List *path)
{
	if (maze == NULL || path == NULL || path->head == NULL)
	{
		return;
	}

	FILE *fp = fopen("output.txt", "w");
	if (fp == NULL)
	{
		fprintf(stderr, "Creating output.txt has failed.\n");
		return;
	}

	size_t row = maze->rows;
	size_t col = maze->cols;

	Point *data = deep_copy_points(maze);
	replace_points(data, col, path);

	/* buffer size == 2n */
	char *buf = (char *)calloc((col << 1), sizeof(char));
	Point *dp = data;

	for (size_t i = 0; i < row; i++)
	{
		char *bp = buf;

		for (size_t j = 0; j < col; j++)
		{
			*bp = TO_CHAR(dp->kind);
			bp++;
			*bp = ' ';
			bp++;
			dp++;
		}
		*(bp-1) = '\0';

		fprintf(fp, "%s\n", buf);
	}

	PathInfo *info = path->head->data;
	fprintf(fp, "Length: %ld\n", info->length);
	fprintf(fp, "Time: %ld\n", info->movement);

	free(buf);
	free(data);
	fclose(fp);
}

void free_shortest_path(List *path)
{
	while (path->count)
	{
		List *p = pop(path);

		/* Expects the first node to be of PathInfo. */
		PathInfo *t = pop(p);
		free(t);

		/* Free the rest of it. */
		while (p->count)
		{
			pop(p);
		}
		free(p);
	}

	free(path);
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
size_t manhattan_distance(Point *s, Point *d)
{
	size_t x1 = s->x;
	size_t x2 = d->x;

	size_t y1 = s->y;
	size_t y2 = d->y;

	size_t d1 = x1 > x2 ? x1 - x2 : x2 - x1;
	size_t d2 = y1 > y2 ? y1 - y2 : y2 - y1;

	return d1 + d2;
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

/* Locate a point of given kind from (i, j). */
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
	}

	if (data == end)
	{
		// fprintf(stderr, "There is no %d in the matrix.\n", point);
		return NULL;
	}

	return data;
}

static Point *locate_multiple_point(MazeMat *src, MazeKind kind)
{
	static List *points = NULL;

	if (points == NULL)
	{
		size_t i = 0;
		size_t j = 0;

		points = init_list();

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
	}

	if (points->count)
	{
		return dequeue(points);
	}
	else
	{
		free(points);
		points = NULL;

		return NULL;
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

static Point *deep_copy_points(MazeMat *src)
{
	if (src == NULL || src->data == NULL)
	{
		return NULL;
	}

	size_t len = src->rows * src->cols;
	Point *data = (Point *)calloc(len, sizeof(Point));
	Point *pd = data;
	Point *ps = src->data;

	for (size_t i = 0; i < len; i++)
	{
		*pd = *ps;
		pd++;
		ps++;
	}

	return data;
}

/*
 * Replace ROAD with SHORTEST_PATH.
 * Note that the first node of 'path'
 * is information of that.
 */
static void replace_points(Point *data, size_t stride, List *path)
{
	if (data == NULL || path == NULL || path->count < 2)
	{
		return;
	}

	Node *node = path->head->next->next;
	Node *tail = path->tail;

	while (node != tail)
	{
		Point *p = node->data;
		data[p->x * stride + p->y].kind = SHORTEST_PATH;
		node = node->next;
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
	size_t stride = maze->cols;

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

PathInfo *create_info(size_t length, size_t movement)
{
	PathInfo *info = (PathInfo *)calloc(1, sizeof(PathInfo));
	info->length = length;
	info->movement = movement;

	return info;
}

