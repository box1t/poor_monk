#include <iostream>   // для ввода/вывода C++
#include <vector>     // для работы с контейнерами C++
#include <thread>

void pth_main(int rank, std::vector<double>& results, int start, int end) {
    double local_sum = 0.0;
    for (int i = start; i <= end; ++i) {
        local_sum += 1.0 / i;
    }
    std::cout << rank << ">\tfrom:\t"<< start << "\tto:\t" << end << std::endl;
    results[rank] = local_sum;
}

int main(int argc, char** argv) {
    std::vector<std::thread> threads;
    int N = std::stoi(argv[1]);
    int size = std::stoi(argv[2]);
    std::vector<double> results(size, 0);

    // Разделим на части с учетом возможного остатка
    int chunk_size = (N + size - 1) / size;
    int start = 1;
    int rank = 0;

    for(; rank < size - 1; ++rank){ 
	threads.emplace_back(pth_main, rank, std::ref(results), start, start + chunk_size - 1);
	start += chunk_size;
    }
    pth_main(rank, std::ref(results), start, N);

    for(auto& th: threads){
	th.join();
    }

    double total_sum = 0;
    for(double i : results){
	total_sum += i;
    }
    std::cout << "Total sum of results: " << total_sum << std::endl;

    return 0;
}
