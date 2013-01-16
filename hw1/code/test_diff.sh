#!/bin/bash

alg=2
dims=(128 256 512 1024 1400 2048)

for i in "${dims[@]}"
do
	./matrix_multiply -n $i -a $alg >> running_times_3
done	

