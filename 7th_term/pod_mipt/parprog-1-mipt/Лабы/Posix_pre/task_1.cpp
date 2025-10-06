#include <iostream>   // для ввода/вывода C++
#include <vector>     // для работы с контейнерами C++

#include <thread>

void pth_main(int rank, int size) {
    std::this_thread::sleep_for(std::chrono::milliseconds(size-rank));
    std::cout << "Hello world! rank:" << rank << " size:" << size << std::endl;
}

int main(int argc, char** argv) {
    int size = std::stoi(argv[1]);
    std::vector<std::thread> pth_id_arr;

    for(int i = 0; i < size; i++){
	pth_id_arr.emplace_back(pth_main, i, size);
    }

    for(auto& th: pth_id_arr){
	th.join();
    }
    return 0;
}
