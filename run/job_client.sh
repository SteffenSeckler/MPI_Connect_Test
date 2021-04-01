#!/bin/bash
#SBATCH -J job_cm2_client
#SBATCH -o ./out/%x.%j.%N.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=cm2_tiny
#SBATCH --partition=cm2_tiny
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
##SBATCH --mail-type=end
##SBATCH --mail-user=insert_your_email_here
#SBATCH --export=NONE
#SBATCH --time=00:10:00
  
module load slurm_setup

module switch intel-mpi intel-mpi/2019.7.217
module list

export FI_LOG_LEVEL=debug
export I_MPI_OFI_PROVIDER=verbs
hname=$(cat hostname_file)
echo "nameserver=$hname"
sleep 2
mpiexec -nameserver $hname -n 1 ../build-cm2/Client

