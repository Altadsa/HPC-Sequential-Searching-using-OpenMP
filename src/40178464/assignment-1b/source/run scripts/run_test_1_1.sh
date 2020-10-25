#!/bin/bash

# Run omp 1 with no scheduling strategy specified

#---------------
# SLURM COMMANDS
#---------------

#SBATCH --job-name=somp_1

#SBATCH --ntasks=1

#SBATCH --cpus-per-task=4

#SBATCH -o outputs/test1/somp1_1.out

#SBATCH -e outputs/test1/somp1_1.err

#----------------
# OPENMP SPECIFIC
#----------------


gcc -fopenmp -std=c11 searching_OMP_1.c -o searching_OMP_1

export OMP_NUM_THREADS=1

echo "Searching test1 using searching_OMP_1"

./searching_OMP_1 1 1 1

echo "Finished Search"

export OMP_NUM_THREADS=2

	
for i in $(seq 10)
do
	
	date

	echo "Searching test1 using searching_OMP_1"

	./searching_OMP_1 1 2 2

	echo "Finished Search"

	date

done


