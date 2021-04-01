#!/bin/bash
#SBATCH -J job_mpp3_server
#SBATCH -o ./out/%x.%j.%N.out
#SBATCH -D ./
#SBATCH --get-user-env
#SBATCH --clusters=mpp3
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
##SBATCH --mail-type=end
##SBATCH --mail-user=insert_your_email_here
#SBATCH --export=NONE
#SBATCH --time=08:00:00
  
module load slurm_setup
module unload devEnv/Intel/2019
module load intel
module switch mpi.intel mpi.intel/2019.7
module list

export FI_LOG_LEVEL=debug
export I_MPI_OFI_PROVIDER=tcp

hname=$(hostname)
#hname=$(host $(hostname) | cut -d' ' -f 4)
#hname=$(host $(hostname) | cut -d' ' -f 1)
echo $hname | tee hostname_file
hydra_nameserver&
sleep 2
mpiexec -nameserver $hname -n 1 ../build-mpp3/Server
rm hostname_file
