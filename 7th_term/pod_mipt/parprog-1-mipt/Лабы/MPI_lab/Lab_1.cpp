#include <mpi.h>
#include <iostream>
#include <vector>

// du/dt + A * du/dx = F(t, x)
const double A = 5;
// F(t, x)
double F(double t, double x) {
    return 0;
}
// Н.У.: u(t=0, x)
double u_0_x(double x) {
    return 1;
}
// Н.У.: u(t, x=0)
double u_t_0(double t) {
    return 1;
}

// 0 <= t <= T
// 0 <= x <= X
const double T = 1;
const double X = 1;

// Количество шагов сетки по времени и координате
//const int N_t = 5;
const int N_x = 1000000;

// Ширина шага сетки
const double d_x = X / N_x;
//const double d_t = T / N_t;


int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N_t = std::stoi(argv[1]);
    double d_t = T / N_t;

    // Для замера времени исполнения
    double time_start = 0, time_end = 0;
    if(rank == 0){
        time_start = MPI_Wtime();
    }

    // Определение границ суммирования
    int partition = N_x / size;
    int idx_x_min = partition * rank + 1;   // i_min * d_x ->
    int idx_x_max = partition * (rank + 1); // -> i_max * d_x
    if(rank == size - 1){                   // -> N_x * d_x
        idx_x_max = N_x;
    }
    partition = idx_x_max - idx_x_min + 1; // Кол-во точек сетки, которое вычисляет процесс

        
    // Векторы для решения на текущем и следующем временном слое
    std::vector<double> u_curr(partition + 1); // +1 для граничного условия
    std::vector<double> u_next(partition + 1); // +1 для граничного условия

    // Инициализация начального условия
    for (int i = -1; i < partition; ++i) {
        u_curr[i+1] = u_0_x((idx_x_min + i) * d_x);
    }

    // Главный цикл по времени
    for (double t = 0; t < T; t+=d_t) {
        // Обмен граничными значениями между процессами
        MPI_Request send_req, recv_req;
        if (rank != size-1) {
            // Отправляем последнее значение следующему процессу
            MPI_Isend(&u_curr[partition], 1, MPI_DOUBLE, rank+1, 0, 
                     MPI_COMM_WORLD, &send_req);
        }
        if (rank != 0) {
            // Получаем значение от предыдущего процесса
            MPI_Irecv(&u_curr[0], 1, MPI_DOUBLE, rank-1, 0, 
                     MPI_COMM_WORLD, &recv_req);
        }
        
        // Вычисляем внутренние точки (не зависящие от границ)
        // 0 - вычисляет другой процесс => получаем из вне. пригодится в будующем.
        // 1 - граничное условие => получаем из вне, что-бы начать счёт
        int i = 2;
        if (rank == 0) {
            i = 1; // Граничное условие известно из Н.У.
        }
        double x = (idx_x_min + i - 1) * d_x; // idx_x_min * d_x - левая граница отрезка сетки по x
        for (i; i <= partition; ++i) {
            u_next[i] = u_curr[i] - A * d_t/d_x * (u_curr[i] - u_curr[i-1]) + d_t * F(x, t);
            x += d_x;
        }

        // Ждем завершения обмена граничными значениями
        if (rank != size-1) {
            MPI_Wait(&send_req, MPI_STATUS_IGNORE);
        }
        if (rank != 0) {
            MPI_Wait(&recv_req, MPI_STATUS_IGNORE);
            
            // Вычисляем граничную точку
            i = 1;
            x = idx_x_min * d_x;
            u_next[i] = u_curr[i] - A * d_t/d_x * (u_curr[i] - u_curr[i-1]) + d_t * F(x, t);
        }
        
        // Граничное условие на левой границе (если процесс 0)
        if (rank == 0) {
            u_next[0] = u_t_0(t + d_t);
        }
        
        std::swap(u_curr, u_next);
        
        //MPI_Barrier(MPI_COMM_WORLD);
    }
    
    // Сбор результатов на главном процессе (опционально)
    if(rank == 0){
        std::vector<double> u(N_x + 1);
        std::vector<int> partition_sizes(size);
        std::vector<int> offsets(size);
        
        offsets[0] = 0;
        for (int i = 1; i < size; ++i) {
            offsets[i] = i * partition + 1 ; // +1 для учёта 0 элемента из Н.У. для rank = 0
        }
        
        for (int i = 0; i < size - 1; ++i) {
            partition_sizes[i] = offsets[i + 1] - offsets[i];
        }
        partition_sizes[size - 1] = (N_x + 1) - offsets[size - 1];

        MPI_Gatherv(u_curr.data(), partition + 1, MPI_DOUBLE, u.data(), partition_sizes.data(), offsets.data(), MPI_DOUBLE, 0, MPI_COMM_WORLD);

        // Вывод и обработка
        for (size_t i = 0; i < u.size(); ++i) {
            std::cout << i*d_t << " , " << u[i] << std::endl;
        }
        
        double time_end = MPI_Wtime();
        std::cout << "P:"<< size << " Nt:" << N_t <<" Time:" << ((time_end - time_start)*1000) << "ms" << std::endl;

    }else{
        MPI_Gatherv(u_curr.data() + 1, partition, MPI_DOUBLE, NULL, NULL, NULL, NULL, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
