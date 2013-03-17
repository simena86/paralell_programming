#ifndef _bfs_
#define _bfs_


#include "headers.h"

int computeBFSEdges(int start,unsigned int ** adjTable, int n,unsigned int * adjTableElementSize, int ** edgeTable);

void computeBFSPath(int start, int goal,unsigned int ** adjTable, int n,unsigned int * adjTableElementSize, int maxNumEdges, int * pathTable, int * pathSize);

#endif
