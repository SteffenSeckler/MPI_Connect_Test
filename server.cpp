#include <iostream>
#include <mpi.h>

int main(int argc, char **argv) {
	std::cout << "Hello, from Server!" << std::endl;

	MPI_Init(&argc, &argv);

	int initial_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &initial_rank);
	int initial_size;
	MPI_Comm_size(MPI_COMM_WORLD, &initial_size);

	char port_name[MPI_MAX_PORT_NAME];

	MPI_Comm inter_comm;
	if (initial_rank == 0) {
		MPI_Info info;
		MPI_Info_create(&info);
		MPI_Info_set(info, "ompi_global_scope", "true");

		MPI_Open_port(info, port_name);

		MPI_Publish_name("Test", info, port_name);
		std::cout << "Published port " << port_name << std::endl;

		std::cout << "Accepting comm (Rank: " << initial_rank << ")!" << std::endl;
		MPI_Comm_accept(port_name, info, 0, MPI_COMM_WORLD, &inter_comm);
		std::cout << "Accepted comm (Rank: " << initial_rank << ")!" << std::endl;

		std::cout << "Unpublishing port!" << std::endl;
		MPI_Unpublish_name("Test", info, port_name);

	} else {
		std::cout << "Accepting comm (Rank: " << initial_rank << ")!" << std::endl;
		MPI_Comm_accept(port_name, MPI_INFO_NULL, 0, MPI_COMM_WORLD, &inter_comm);
		std::cout << "Accepted comm (Rank: " << initial_rank << ")!" << std::endl;
	}

	MPI_Comm new_comm;
	MPI_Intercomm_merge(inter_comm, 0, &new_comm);

	int new_rank;
	MPI_Comm_rank(new_comm, &new_rank);
	int new_size;
	MPI_Comm_size(new_comm, &new_size);

	std::cout << "Old rank: " << initial_rank << ", new rank: " << new_rank << std::endl;
	std::cout << "Old size: " << initial_size << ", new size: " << new_size << std::endl;

	std::cout << "Disconnecting comm!" << std::endl;
	MPI_Comm_disconnect(&inter_comm);

	if (initial_rank == 0) {
		std::cout << "Closing port!" << std::endl;
		MPI_Close_port(port_name);
		std::cout << "Port closed!" << std::endl;
	}

	MPI_Finalize();
	return 0;
}
