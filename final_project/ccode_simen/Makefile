
main:  collision_detection.c freeConfigSpace.c generate_polygons.c functions.c 
	gcc -O3 -o x.out collision_detection.c freeConfigSpace.c generate_polygons.c visualization.c gnuplot_i.c functions.c -ljansson -lm 

clean: 
	rm *.out

mpi: computeAdjTableForFreeCSpacePoints.c test3LinkGrid.c  collision_detection.c freeConfigSpace_mpi.c generate_polygons.c functions.c communication.c 
	mpicc  -O3 -Ofast -o x.out test3LinkGrid.c collision_detection.c computeAdjTableForFreeCSpacePoints.c freeConfigSpace_mpi.c generate_polygons.c communication.c visualization.c gnuplot_i.c functions.c bfs.c fifo.c computeNearestPoint.c -ljansson -lm 

run:
	mpirun -np 1 ./x.out

halton: computeNearestPoint.c computeAdjTableForFreeCSpacePoints.c test3LinkGrid.c  collision_detection.c freeConfigSpace_mpi.c generate_polygons.c halton_sequence.c communication.c 
	mpicc  -O3 -Ofast -o x.out computeNearestPoint.c test3LinkGrid.c collision_detection.c computeAdjTableForFreeCSpacePoints.c freeConfigSpace_mpi.c generate_polygons.c communication.c visualization.c gnuplot_i.c halton_sequence.c bfs.c fifo.c -ljansson -lm 
