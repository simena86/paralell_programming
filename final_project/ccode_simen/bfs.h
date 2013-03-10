#ifndef _bfs_
#define _bfs_


#include "headers.h"

int computeBFSEdges(int start, int ** adjTable, int n, int * adjTableElementSize, int ** edgeTable);

int computeBFSPath(int start, int goal, int ** adjTable, int n, int * adjTableElementSize, int maxNumEdges);

#endif
