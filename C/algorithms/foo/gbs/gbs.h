#ifndef GBS_H

#define GBS_H
#include <stdio.h>
#include <stdlib.h>
#include "maze_mat.h"
#include "util/my_list.h"
#include "util/priority_queue.h"

List *greedy_bestfirst_search(MazeMat *maze);

#endif

