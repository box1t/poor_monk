
```c++
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::vector<int> numbers;
std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void GenNumber() {
    for(int i=0; i<100; i++) {
        numbers.push_back(i);
    }
    
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_one();
}

void printNumbers() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });

    // Вывод массива на экран
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::thread t1(GenNumber);
    std::thread t2(printNumbers);

    t1.join();
    t2.join();

    return 0;
}

```

