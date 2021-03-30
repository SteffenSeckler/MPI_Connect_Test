#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
	std::cout << "Hello, from Client!" << std::endl;

	MPI_Init(&argc, &argv);

	int initial_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &initial_rank);
	int initial_size;
	MPI_Comm_size(MPI_COMM_WORLD, &initial_size);

	char port_name[MPI_MAX_PORT_NAME];

	MPI_Comm inter_comm;
	if (initial_rank == 0) {
		MPI_Lookup_name("Test", MPI_INFO_NULL, port_name);
		std::cout << "Name lookup done: " << port_name << std::endl;
	}

	MPI_Comm_connect(port_name, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &inter_comm);
	std::cout << "Comm connected!" << std::endl;

	MPI_Comm new_comm;
	MPI_Intercomm_merge(inter_comm, 1, &new_comm);

	int new_rank;
	MPI_Comm_rank(new_comm, &new_rank);
	int new_size;
	MPI_Comm_size(new_comm, &new_size);

	std::cout << "Old rank: " << initial_rank << ", new rank: " << new_rank << std::endl;
	std::cout << "Old size: " << initial_size << ", new size: " << new_size << std::endl;

	std::cout << "Disconnecting comm!" << std::endl;
	MPI_Comm_disconnect(&inter_comm);
	std::cout << "Comm disconnected!" << std::endl;

	MPI_Finalize();
	return 0;
}
