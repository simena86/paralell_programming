#include <stdio.h>
#include "fifo.h"


// PORBLEM!!!! -> maxsize in fifo queue


int computeBFSEdges(int start, int ** adjTable, int n, int * adjTableElementSize, int ** edgeTable){
	// Returns the number of edges in the BFS-tree
	printf("computeBFSEdges\n");
	int i,v,idx, iter,a;
	int marked[n];

	iter = 0;
	//mark all nodes as unvisited, except for start
	for (i=0;i<n;i++){
		marked[i]=-1;
	}
	marked[start] = 0;
	
	// prepare list of vertices to visit and BFS edges
	add(start);
	
	// loop while the list of vertices to visit is nonempty
	while((a = empty()) == 0){
 		// pick first vertex and remove it from list
		v = s.queue[s.front];
		//printf("v: %d, size: %d\n", v, adjTableElementSize[v]);

		delete();
 		// find all neighbors of vertex that are unmarked
		for(i=0;i<adjTableElementSize[v];i++){
			//printf("halla2\n");
			idx = adjTable[v][i];
			if(marked[idx] == -1){
				// found an unmarked neighbor, hence mark it
			      	// and add it to list of vertices to explore from
			        // and save the useful edge
				marked[idx] = marked[v] + 1;
				add(idx);	// add to fifo queue
				edgeTable[iter][0] = v;
				edgeTable[iter][1] = idx;
				iter++;
			}
		}
	}
	return iter;
}

int computeBFSPath(int start, int goal, int ** adjTable, int n, int * adjTableElementSize, int maxNumEdges){
	// Return the number of edges en the shortest path
	// IMPORTAINT: The shortest path is reversed i.e. it starts at the goal
	
	int i,j,tmp, bContinue; 
	int iter = 0;
	
	// Set up edgeTable
	int ** edgeTable = (int **)malloc(sizeof(int*)* maxNumEdges);
	for (i=0;i<maxNumEdges;i++){
		edgeTable[i] = (int *)malloc(sizeof(int)* 2);
	} 
	for(i=0;i<maxNumEdges;i++){
		for(j=0;j<2;j++){
			edgeTable[i][j] = -1;
		}
	}
	

	
	// Compute the BFS-Edges of the graph
	int numBFSEdges = computeBFSEdges(start,adjTable,n,adjTableElementSize, edgeTable);
	// Print the edgeTable
	for(i=0;i<maxNumEdges;i++){
		printf("%d, %d\n", edgeTable[i][0], edgeTable[i][1]);
	}

	// Set up the path table
	int ** path = (int **)malloc(sizeof(int*)* numBFSEdges);
	for (i=0;i<numBFSEdges;i++){
		path[i] = (int *)malloc(sizeof(int)* 2);
	} 
	for(i=0;i<numBFSEdges;i++){
		for(j=0;j<2;j++){
			path[i][j] = -1;
		}
	}
	tmp = goal;
	bContinue = 1;
	while(bContinue){
		bContinue = 0;
		for(i=0;i<numBFSEdges;i++){
			if(edgeTable[i][1] == tmp){
				tmp = edgeTable[i][0];
				path[iter][0]= edgeTable[i][0];
				path[iter][1]= edgeTable[i][1];
				iter++;
				bContinue = 1;
				break;
			}
		}
	}
	// Print the path
	for(i=0;i<iter;i++){
		printf("%d, %d\n", path[i][0], path[i][1]);
	}
	
	return iter; 
}

void main()
{
	
	int i;

	s.front = 0;
	s.rear = 0;
	int free_cs_size = 5;
	int free_cs_size2 = 3;
	
	int ** adjTable = (int **)malloc(sizeof(int*)* free_cs_size);
	for (i=0;i<free_cs_size;i++){
		adjTable[i] = (int *)malloc(sizeof(int)* free_cs_size2);
	} 
	int * adjTableElementSize = (int*)malloc(sizeof(int)* free_cs_size);

	adjTable[0][0] = 1;
	adjTable[1][0] = 0;
	adjTable[1][1] = 2;
	adjTable[1][2] = 3;
	adjTable[2][0] = 1;
	adjTable[2][1] = 4;
	adjTable[2][2] = 3;
	adjTable[3][0] = 1;
	adjTable[3][1] = 2;
	adjTable[4][0] = 2;

	adjTableElementSize[0] = 1;
	adjTableElementSize[1] = 3;
	adjTableElementSize[2] = 3;
	adjTableElementSize[3] = 2;
	adjTableElementSize[4] = 1;

	int numInSPath = computeBFSPath(0, 4, adjTable, free_cs_size, adjTableElementSize, 20);
}
