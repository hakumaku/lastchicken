#ifndef MAZE_MAT_H

#define MAZE_MAT_H
#include <stdio.h>
#include <stdlib.h>
#include "util/my_string.h"
#include "util/my_list.h"

typedef struct maze_mat MazeMat;
typedef struct point_data Point;
typedef struct path_info PathInfo;
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
	/* A* search */
	size_t distance;
	bool eval;
};

struct path_info
{
	size_t length;
	size_t movement;
};

MazeMat *init_maze(const char *text_file);
List *construct_path(MazeMat *maze, Point *end);
void clearup_maze(MazeMat *src);
void free_maze(MazeMat *src);
void free_shortest_path(List *path);
void free_shortest_paths(List *paths);

void print_maze(MazeMat *src);
void print_shortest_path(List *paths);
void write_shortest_path(MazeMat *maze, List *path);

Point *locate_starting(MazeMat *src);
Point *locate_ending(MazeMat *src);
Point *look_around(MazeMat *src, Point *p);
Point *get_previous_point(MazeMat *maze, Point *p);
size_t manhattan_distance(Point *s, Point *d);
size_t nearest_manhattan_distance(Point *s, List *ends);

PathInfo *create_info(size_t length, size_t movement);

#endif

