#include <iostream>   // для ввода/вывода C++
#include <vector>     // для работы с контейнерами C++
#include <thread>

#include <mutex>
std::mutex mtx; // global sync mutex


//каждый процесс прибавляет 1 в общую ячейку 
int size = 100;
int max = 10000000;

void pth_main(int rank, long int& total_sum) {
    std::cout << rank << "> Start" << std::endl;
    for (int i = 0; i < max; ++i) {

	// global mutex critical section block
	{
            std::lock_guard<std::mutex> lock(mtx);
            total_sum++;
	}

    }
    std::cout << rank << "> Finish" << std::endl;
}

int main(int argc, char** argv) {
    std::vector<std::thread> threads;

    long int results = 0;

    for(int rank = 0; rank < size; ++rank){ 
	threads.emplace_back(pth_main, rank, std::ref(results));
    }

    for(auto& th: threads){
	th.join();
    }

    std::cout << "TOTAL SUM:" << results << std::endl;

    return 0;
}
