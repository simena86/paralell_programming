main: computeNearestPoint.c computeAdjTableForFreeCSpacePoints.c test3LinkGrid.c  collision_detection.c freeConfigSpace_mpi.c generate_polygons.c halton_sequence.c communication.c 
	mpicc  -O3 -o x.out ./src/*.c computeNearestPoint.c test3LinkGrid.c collision_detection.c computeAdjTableForFreeCSpacePoints.c freeConfigSpace_mpi.c generate_polygons.c communication.c  halton_sequence.c bfs.c fifo.c  -lm 

clean: 
	rm *.out *.o 

