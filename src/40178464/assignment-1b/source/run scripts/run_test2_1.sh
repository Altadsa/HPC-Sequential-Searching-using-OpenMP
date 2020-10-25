#!/bin/bash

#---------------
# SLURM COMMANDS
#---------------

#SBATCH --job-name=somp_2

#SBATCH --ntasks=1

#SBATCH --cpus-per-task=4

#SBATCH -o outputs/test2/somp_2_1.out

#SBATCH -e outputs/test2/somp_2_1.err

#----------------
# OPENMP SPECIFIC
#----------------

export OMP_NUM_THREADS=64

gcc -fopenmp -std=c11 searching_OMP_2.c -o searching_OMP_2

date

echo "Searching test2 using searching_OMP_2"

./searching_OMP_2 2 1 64

echo "Finished Search"

date