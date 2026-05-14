#include <mpi.h>
#include <iostream>

void send_data(int cur_rank, int rank) {
    MPI_Send(NULL, 0, MPI_INT, rank, 0, MPI_COMM_WORLD);
}

void get_response(int cur_rank, int rank) {
    MPI_Status status;	
    MPI_Recv(NULL, 0, MPI_INT, rank, 0, MPI_COMM_WORLD, &status);
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        int data = 0;
        int data_max = std::stoi(argv[1]);
        
        double start = MPI_Wtime();

        do {
            send_data(rank, rank + 1);
            get_response(rank, size - 1);
            data++;
        } while (data < data_max);
        
        double finish = MPI_Wtime();
        
        std::cout << (finish - start) / data * size << std::endl;

    } else if (rank == size - 1){
        while (true)
        {
            get_response(rank, rank - 1);
            send_data(rank, 0);    
        }
    }else{
        while (true)
        {
            get_response(rank, rank - 1);
            send_data(rank, rank + 1);
        }
    }
    MPI_Abort(MPI_COMM_WORLD, 0); 
    return 0;
}
