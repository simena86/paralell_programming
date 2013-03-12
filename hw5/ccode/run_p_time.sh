#!/bin/bash

./life 2000 1000 -cilk_set_worker_count=1 >> log_time_vs_p
./life 2000 1000 -cilk_set_worker_count=2 >> log_time_vs_p
./life 2000 1000 -cilk_set_worker_count=3 >> log_time_vs_p
./life 2000 1000 -cilk_set_worker_count=4 >> log_time_vs_p
./life 2000 1000 -cilk_set_worker_count=5 >> log_time_vs_p
./life 2000 1000 -cilk_set_worker_count=6 >> log_time_vs_p
./life 2000 1000 -cilk_set_worker_count=7 >> log_time_vs_p
./life 2000 1000 -cilk_set_worker_count=8 >> log_time_vs_p
