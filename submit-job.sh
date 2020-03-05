#!/bin/bash
#
# You should only work under the /scratch/users/<username> directory.
#
# Example job submission script
#
# -= Resources =-
#
#SBATCH --job-name=nqueens-job
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=16
#SBATCH --partition=short
#SBATCH --time=00:30:00
#SBATCH --output=nqueens.out

################################################################################
##################### !!! DO NOT EDIT ABOVE THIS LINE !!! ######################
################################################################################
# Set stack size to unlimited
echo "Setting stack size to unlimited..."
ulimit -s unlimited
ulimit -l unlimited
ulimit -a
echo

echo "Running Job...!"
echo "==============================================================================="
echo "Running compiled binary..."

#serial version
echo "Serial version..."
./s

#parallel version
echo "A - 1 thread"
export OMP_NUM_THREADS=1
export KMP_AFFINITY=verbose,granularity=fine,compact
export OMP_NESTED=true
./a

echo "A - 2 threads"
export OMP_NUM_THREADS=2
export KMP_AFFINITY=verbose,granularity=fine,compact
export OMP_NESTED=true
./a

echo "A - 4 threads"
export OMP_NUM_THREADS=4
export KMP_AFFINITY=verbose,granularity=fine,compact
export OMP_NESTED=true
./a

echo "A - 8 threads"
export OMP_NUM_THREADS=8
export KMP_AFFINITY=verbose,granularity=fine,compact
export OMP_NESTED=true
./a

echo "A - 16 threads"
export OMP_NUM_THREADS=16
export KMP_AFFINITY=verbose,granularity=fine,compact
export OMP_NESTED=true
./a

echo "A - 32 threads"
export OMP_NUM_THREADS=32
export KMP_AFFINITY=verbose,granularity=fine,compact
export OMP_NESTED=true
./a