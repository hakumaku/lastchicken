#ifndef GBS_H

#define GBS_H
#include <stdio.h>
#include <stdlib.h>
#include "maze_mat.h"
#include "my_list.h"
#include "priority_queue.h"

List *greedy_bestfirst_search(MazeMat *maze);
List *greedy_bestfirst_nearest_search(MazeMat *maze);

#endif

