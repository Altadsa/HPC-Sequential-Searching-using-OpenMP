#!/bin/bash

#---------------
# SLURM COMMANDS
#---------------

# Run sequential search and omp 0 search

#SBATCH --job-name=somp_1

#SBATCH --ntasks=1

#SBATCH --cpus-per-task=4

#SBATCH -o outputs/test1/somp1_0.out

#SBATCH -e outputs/test1/somp1_0.err

gcc searching_sequential.c -o searching_sequential -std=c11

echo

date

echo "Starting test1 using searching_sequential"

./searching_sequential 1

echo "Finished searching_sequential for test1"

date

echo

#----------------
# OPENMP SPECIFIC
#----------------

export OMP_NUM_THREADS=2

export OMP_SCHEDULE="static,2"

gcc -fopenmp -std=c11 searching_OMP_0.c -o searching_OMP_0

#date

echo "Searching test1 using searching_OMP_0"

./searching_OMP_0 1 2 2

echo "Finished Search"

#date

echo

gcc -fopenmp -std=c11 searching_OMP_1.c -o searching_OMP_1

date

echo "Searching test1 using searching_OMP_1"

./searching_OMP_1 1 2 2

echo "Finished Search"

date
