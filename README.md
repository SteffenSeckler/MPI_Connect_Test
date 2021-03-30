# MPI_Connect_Test

Example Server-Client application for using MPI_Comm_connect and MPI_Comm_accept.

Using `MPI_Comm_accept` and `MPI_Comm_connect`, two mpi communicators that are started from two different mpirun
commands are joined.

## Running

For this test an external nameserver is needed. The client has to be started AFTER the server!

- MPICH/Intel MPI: hydra_nameserver can be used (see `build_and_execute_mpich.sh`):
    1. Start hydra_nameserver on some host using `hydra_nameserver`
    2. Start the server. Do not forget to specify the nameserver:
       `mpirun -n 2 -nameserver ${HOSTNAME} ./Server`
       Here, the hostname has to be the name of the host where the nameserver is running (e.g. localhost).
    3. Start the client. Again the hostname has to be specified!
       `mpirun -n 2 -nameserver ${HOSTNAME} ./Client`


- OpenMPI: The use of openmpi is currently untested and discouraged, as some bugs produce deadlocks or give
  errors (https://github.com/openpmix/prrte/issues/398#issuecomment-795628306
  , https://github.com/open-mpi/ompi/issues/6916). For some versions of OpenMPI the following should work:
    1. Start ompi-server using `ompi-server [--no-deamonize] -r urifile`
    2. Start the server: `mpirun -n 2 --ompi-server file:urifile ./Server`
    3. Start the client: `mpirun -n 2 --ompi-server file:urifile ./Client`

## Further reading

- Stackoverflow post explaining the (outdated) openmpi server variant: https://stackoverflow.com/a/15008715/9701176
- New variant using PRRTE (documentation is currently lacking): https://github.com/openpmix/prrte/issues/398#issuecomment-795628306, 