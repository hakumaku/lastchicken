#ifndef MAZE_MAT_H

#define MAZE_MAT_H
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "my_list.h"

#define DEAD_END	0	
#define FOUND_EXIT	2

typedef struct maze_mat MazeMat;
typedef struct point_data Point;
typedef enum maze_kind MazeKind;
typedef enum maze_prev MazePrev;

enum maze_kind
{
	OUT_OF_INDEX = 0,
	WALL,
	ROAD,
	STARTING_POINT,
	ENDING_POINT,
	SHORTEST_PATH
};

enum maze_prev
{
	NONE = 0,
	UP,
	DOWN,
	LEFT,
	RIGHT
};

struct maze_mat
{
	size_t rows;
	size_t cols;
	Point *data;
};

struct point_data
{
	size_t x;
	size_t y;
	MazeKind kind;
	MazePrev from;
	/* Maze with multiple exits. */
	bool eval;
};

MazeMat *init_maze(const char *text_file);
void free_maze(MazeMat *src);
void print_maze(MazeMat *src);

Point *locate_starting(MazeMat *src);
Point *locate_ending(MazeMat *src);
Point *look_around(MazeMat *src, Point *p);
Point *get_previous_point(MazeMat *maze, Point *p);
void print_shortest_path(List *paths);
/* Writing */

#endif

