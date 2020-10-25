#!/bin/bash

#---------------
# SLURM COMMANDS
#---------------

#SBATCH --job-name=somp_2

#SBATCH --ntasks=1

#SBATCH --cpus-per-task=4

#SBATCH -o outputs/test2/somp_2.out

#SBATCH -e outputs/test2/somp_2.err

gcc searching_sequential.c -o searching_sequential -std=c11

echo

date

echo "Starting test2 using searching_sequential"

./searching_sequential 2

echo "Finished searching_sequential for test2"

date

echo

#----------------
# OPENMP SPECIFIC
#----------------

export OMP_NUM_THREADS=64

gcc -fopenmp -std=c11 searching_OMP_1.c -o searching_OMP_1

date

echo "Searching test2 using searching_OMP_1"

./searching_OMP_1 2 1 64

echo "Finished Search"

date
