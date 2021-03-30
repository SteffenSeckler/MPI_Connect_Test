cmake_minimum_required(VERSION 3.9)
project(MPI_Connect_Test)

set(CMAKE_CXX_STANDARD 11)

find_package(MPI REQUIRED)
if (NOT ${MPI_CXX_FOUND})
    message(FATAL_ERROR "cxx mpi could not be found")
endif ()

add_executable(Server server.cpp)
target_link_libraries(Server
        PUBLIC
        MPI::MPI_CXX)

add_executable(Client client.cpp)
target_link_libraries(Client
        PUBLIC
        MPI::MPI_CXX)