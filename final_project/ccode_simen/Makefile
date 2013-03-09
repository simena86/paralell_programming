
main:  collision_detection.c freeConfigSpace.c generate_polygons.c functions.c 
	gcc -O3 -o x.out collision_detection.c freeConfigSpace.c generate_polygons.c visualization.c gnuplot_i.c functions.c -ljansson -lm 

clean: 
	rm *.out

mpi: computeAdjTableForFreeCSpacePoints.c test3LinkGrid.c  collision_detection.c freeConfigSpace_mpi.c generate_polygons.c functions.c communication.c 
	mpicc -O3 -o x.out test3LinkGrid.c collision_detection.c computeAdjTableForFreeCSpacePoints.c freeConfigSpace_mpi.c generate_polygons.c communication.c visualization.c gnuplot_i.c functions.c -ljansson -lm 

run:
	mpirun -np 3 ./x.out
