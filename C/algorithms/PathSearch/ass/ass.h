#ifndef ASS_H

#define ASS_H
#include <stdio.h>
#include <stdlib.h>
#include "maze_mat.h"
#include "my_list.h"
#include "priority_queue.h"

List *astar_search(MazeMat *maze);
List *astar_nearest_search(MazeMat *maze);

#endif

