#!/bin/bash

#SBATCH --job-name=ssa
#SBATCH --output=/users/40178464/Assignment1a-dir/outputs/searching_sequential.out

echo "Compile Searching Sequential with compiler optimization (O2)"

gcc -O2 searching_sequential.c -o  searching_sequential_2
date
./searching_sequential_2
date

echo "Compile Searching Sequential without compiler optimization (O0)"

gcc -O0 searching_sequential.c -o searching_sequential_0
date
./searching_sequential_0
date
