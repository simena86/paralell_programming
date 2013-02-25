#!/bin/bash

rm cilkview.out
touch cilkview.out

echo "1 processors" >> cilkview.out
./innerproduct 1000000 -cilk_set_worker_count=1
echo "2 processors" >> cilkview.out
./innerproduct 1000000 -cilk_set_worker_count=2
echo "3 processors" >> cilkview.out
./innerproduct 1000000 -cilk_set_worker_count=3
echo "4 processors" >> cilkview.out
./innerproduct 1000000 -cilk_set_worker_count=4
echo "5 processors" >> cilkview.out
./innerproduct 1000000 -cilk_set_worker_count=5
echo "6 processors" >> cilkview.out
./innerproduct 1000000 -cilk_set_worker_count=6
echo "7 processors" >> cilkview.out
./innerproduct 1000000 -cilk_set_worker_count=7
echo "8 processors" >> cilkview.out
./innerproduct 1000000 -cilk_set_worker_count=8

mv cilkview.out task2.out
