#!/bin/bash


echo "time vs n running on 8 cores" >> log_time_vs_n_1p
echo "n=500" >> log_time_vs_n_1p
./life 500 1000 -cilk_set_worker_count=1 >> log_time_vs_n_1p
echo "n=1000" >> log_time_vs_n_1p
./life 1000 1000  -cilk_set_worker_count=1 >> log_time_vs_n_1p
echo "n=1500" >> log_time_vs_n_1p
./life 1500 1000  -cilk_set_worker_count=1 >> log_time_vs_n_1p
echo "n=2000" >> log_time_vs_n_1p
./life 2000 1000 -cilk_set_worker_count=1  >> log_time_vs_n_1p
echo "n=2500" >> log_time_vs_n_1p
./life 2500 1000 -cilk_set_worker_count=1  >> log_time_vs_n_1p
echo "n=3000" >> log_time_vs_n_1p
./life 3000 1000 -cilk_set_worker_count=1  >> log_time_vs_n_1p
echo "n=3500" >> log_time_vs_n_1p
./life 3500 1000 -cilk_set_worker_count=1  >> log_time_vs_n_1p
echo "n=4000" >> log_time_vs_n_1p
./life 4000 1000 -cilk_set_worker_count=1  >> log_time_vs_n_1p
echo "n=4500" >> log_time_vs_n_1p
./life 4500 1000 -cilk_set_worker_count=1  >> log_time_vs_n_1p


