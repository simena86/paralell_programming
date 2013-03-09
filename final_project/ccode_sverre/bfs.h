#ifndef _BFS_
#define _BFS_

#include "headers.h"

int computeBFSEdges(int start, int ** adjTable, int n, int * adjTableElementSize, int ** edgeTable);

int computeBFSPath(int start, int goal, int ** adjTable, int n, int * adjTableElementSize, int maxNumEdges);

#endif
