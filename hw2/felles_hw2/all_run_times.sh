#!/bin/bash

dims=(1 2 4 8 16)

for i in "${dims[@]}"
do
	mpirun -machinefile $PBS_NODEFILE -np $i ./assn2 2400 1000 >> running_times
done	

