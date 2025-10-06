#include <mpi.h>
#include <iostream>
#include <cmath>
#include <iomanip>

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 0;
    if (argc == 2) {
        try {
            N = std::stoi(argv[1]);
            if (N <= 0) {
                throw std::invalid_argument("N must be positive.");
            }
            if (N < size) {
                throw std::invalid_argument("N must be greater than or equal to the number of processes.");
            }
        }
        catch(const std::exception& e) {
            if (rank == 0) {
                std::cerr << e.what() << std::endl;
            }
            MPI_Finalize();
            return 1;
        }
    }else{
        if (rank == 0) {
            std::cerr << "Presented " << argc - 1 << " arguments. Expected 1." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }


    // Разделим на части с учетом возможного остатка
    int chunk_size = (N + size - 1) / size; 

    long double local_sum = 0.0;
    int i = rank * chunk_size + 1;
    for (; i <= (rank + 1) * chunk_size && i <= N; ++i) {
        local_sum += 1.0L / i;
    }
    std::cout << std::fixed << std::setprecision(std::numeric_limits<long double>::digits10 + 1);
    std::cout << rank << ">\tfrom:\t"<< rank * chunk_size + 1 << "\tto:\t" << i - 1 <<"\tlocal_sum:\t" << local_sum << std::endl;

    long double total_sum = 0.0;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_LONG_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        std::cout << rank << ">\tfrom:\t"<< 1 << "\tto:\t" << N <<"\ttotal_sum:\t" << total_sum << std::endl;

    }

    MPI_Finalize();
    return 0;
}
