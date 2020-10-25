#!/bin/bash

#SBATCH ntasks=1
#SBATCH cpus-per-task=4

#SBATCH --job-name=ssa
#SBATCH -o outputs/searching_sequential.out
#SBATCH -e outputs/searching_sequential.err

echo "Compile Searching Sequential with compiler optimization (O2)"

date
gcc -O2 searching_sequential.c -o  searching_sequential_2 -std=c11
date
./searching_sequential_2
date

echo "Compile Searching Sequential without compiler optimization (O0)"
date
gcc -O0 searching_sequential.c -o searching_sequential_0 -std=c11
date
./searching_sequential_0
date
