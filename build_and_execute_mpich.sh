#!/usr/bin/env bash
set -e

mkdir -p build
cd build

# build
mpicxx.mpich ../server.cpp -o Server
mpicxx.mpich ../client.cpp -o Client

# Run hydra nameserver
hydra_nameserver&

# Run server
mpirun.mpich -n 2 -nameserver localhost ./Server &
# Run client
mpirun.mpich -n 2 -nameserver localhost ./Client &