#!/bin/bash

#---------------
# SLURM COMMANDS
#---------------

#SBATCH --job-name=somp_0

#SBATCH --ntasks=1

#SBATCH --ntasks-per-core=1

#SBATCH --cpus-per-task=8

#SBATCH -o outputs/test0/somp_01.out

#SBATCH -e outputs/test0/somp_01.err

gcc searching_sequential.c -o searching_sequential -std=c11

date

echo "Starting searching sequential on test0"

./searching_sequential 0

echo "Finished searching sequential on test0"

date

#----------------
# OPENMP SPECIFIC
#----------------

export OMP_NUM_THREADS=64

gcc -fopenmp -std=c11 searching_OMP_0.c -o searching_OMP_0

date

echo "Start Searching Parallel with Scheduling=static"

export OMP_SCHEDULE=static
./searching_OMP_0 0 1 64

echo "Finished Searching Parallel"

date

#gcc -fopenmp -std=c11 searching_OMP_0.c -o searching_OMP_0

echo "Start Searching Parallel with Scheduling=dynamic"

export OMP_SCHEDULE=dynamic
./searching_OMP_0 0 1 64

echo "Finished Searching Parallel"

date

#gcc -fopenmp -std=c11 searching_OMP_0.c -o searching_OMP_0

echo "Start Searching Parallel with Scheduling=guided"

export OMP_SCHEDULE=guided
./searching_OMP_0 0 1 64

echo "Finished Searching Parallel"

date

echo "Start Searching Parallel with Scheduling=auto"

export OMP_SCHEDULE=auto
./searching_OMP_0 0 1 64

echo "Finished Searching Parallel"

date

