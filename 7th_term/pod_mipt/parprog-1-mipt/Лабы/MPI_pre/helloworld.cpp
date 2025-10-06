#include <mpi.h>      // для функций MPI
#include <iostream>   // для ввода/вывода C++
#include <vector>     // для работы с контейнерами C++
#include <string>     // для работы со строками
#include <unistd.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::cout << "Hello World from rank " << rank << " out of " << size << " processors" << std::endl;

    sleep(11);
    MPI_Finalize();
    return 0;
}
