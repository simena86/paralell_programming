#!/bin/bash

rm cilkview.out
touch cilkview.out

echo "1 processors" >> cilkview.out
CILK_NPROC=1
./innerproduct 10000 -cilk_set_worker_count=$CILK_NPROC
./innerproduct 100000 -cilk_set_worker_count=$CILK_NPROC
./innerproduct 1000000 -cilk_set_worker_count=$CILK_NPROC
./innerproduct 10000000 -cilk_set_worker_count=$CILK_NPROC
./innerproduct 100000000 -cilk_set_worker_count=$CILK_NPROC



echo "4 processors" >> cilkview.out
CILK_NPROC=4
./innerproduct 10000 -cilk_set_worker_count=$CILK_NPROC
./innerproduct 100000 -cilk_set_worker_count=$CILK_NPROC
./innerproduct 1000000 -cilk_set_worker_count=$CILK_NPROC
./innerproduct 10000000 -cilk_set_worker_count=$CILK_NPROC
./innerproduct 100000000 -cilk_set_worker_count=$CILK_NPROC

mv cilkview.out task1.out
