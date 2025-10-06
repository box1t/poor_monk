#include <mpi.h>
#include <iostream>

void send_data(int cur_rank, int rank, int data) {
    std::cout << cur_rank << " > Send " << data << " to " << rank << std::endl;
    MPI_Send(&data, 1, MPI_INT, rank, 0, MPI_COMM_WORLD);
}

void get_response(int cur_rank, int rank, int &data) {
    MPI_Status status;
    std::cout << cur_rank << " > Wait data fr" << rank << std::endl;
    MPI_Recv(&data, 1, MPI_INT, rank, 0, MPI_COMM_WORLD, &status);
    std::cout << cur_rank << " > Rciv " << data << " fr " << rank << std::endl;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data = 0;
    if (rank == 0) {
        send_data(rank, rank + 1, data);
        get_response(rank, size - 1, data);
    } else if (rank == size - 1){
        get_response(rank, rank - 1, data);
        send_data(rank, 0, data + 1);
    }else{
        get_response(rank, rank - 1, data);
        send_data(rank, rank + 1, data + 1);
    }

    MPI_Finalize();
    return 0;
}