#!/bin/bash
#SBATCH -J job_mpp3_client
#SBATCH -o ./out/%x.%j.%N.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp3
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
##SBATCH --mail-type=end
##SBATCH --mail-user=insert_your_email_here
#SBATCH --export=NONE
#SBATCH --time=00:10:00
  
module load slurm_setup
module unload devEnv/Intel/2019
module load intel
module switch mpi.intel mpi.intel/2019.7
module list

export FI_LOG_LEVEL=debug
export I_MPI_OFI_PROVIDER=verbs

hname=$(cat hostname_file)
echo "nameserver=$hname"
echo "nameserver host=$(host $hname)"
sleep 2
mpiexec -nameserver $hname -n 1 ../build-mpp3/Client

