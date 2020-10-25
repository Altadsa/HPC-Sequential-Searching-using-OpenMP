#!/bin/bash

#---------------
# SLURM COMMANDS
#---------------

#SBATCH --job-name=somp_1

#SBATCH --ntasks=1

#SBATCH --cpus-per-task=4

#SBATCH -o outputs/test1/somp1_2.out

#SBATCH -e outputs/test1/somp1_2.err

#----------------
# OPENMP SPECIFIC
#----------------

export OMP_NUM_THREADS=2

gcc -fopenmp -std=c11 searching_OMP_1.c -o searching_OMP_1

for n in {1,2,4}
do

for x in {"static","dynamic","guided","auto"}
do
	export OMP_SCHEDULE="$x,$n"
	echo "Scheduling = $OMP_SCHEDULE"
	
	for i in $(seq 10)
	do
	
		date

		echo "Searching test1 using searching_OMP_1 with $OMP_SCHEDULE scheduling."

		./searching_OMP_1 1 2 2

		echo "Finished Search"

		date

	done

done


done



