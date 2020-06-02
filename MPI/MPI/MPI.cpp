#include <iostream>
#include <ostream>

int main_(int argc, char* argv[])
{
    int size, rank;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0)
    {
        int value = 42;
        for (size_t i = 1; i < size; i++)
        {
	        std::cout << "Ready to send " << rank << "-->" << i << std::endl;
            MPI_Ssend(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            std::cout << "Data sent     " << rank << "-->" << i << std::endl;
        }
    }
    else {
        int value = -1;
        //MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << rank << " received from 0 the value " << value << std::endl;
    }

    MPI_Finalize();

    return 0;
}

