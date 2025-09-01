
```c++
`std::lock_guard` - RAII обёртка над `std::mutex::lock/unlock`.
В конструкторе захватывает mutex, в деструкторе его освобождает.
Второй вариант параллельного суммирования:

#include <mutex>
#include <thread>
#include <vector>

int parallel_sum(const std::vector<int>& vec) {
	int length = vec.size();
	int rv = 0;
	std::mutex mtx;
	std::thread t1([&](){
	for (int i = 0; i < length/2; ++i) {
		std::lock_guard<std::mutex> guard(mtx);
		rv += vec[i];
		}
	});
	
  
std::thread t2([&](){
	for (int i = length/2; i < length; ++i) {
		std::lock_guard<std::mutex> guard(mtx);
		rv += vec[i];
		}
	});
	t1.join();
	t2.join();
	return rv;
}
```


```c++
#include <iostream>
#include <vector>
#include <thread>

std::vector<int> vec;
void sumVec(const vec& v1, size_t start, size_t end, const vec& v2, vec& res) {
	for (int i = start; i < end; ++i) {
		res[i] = v1[i] + v2[i];
	}
}
void parallelSum(const vec& v1, const vec& v2, vec& res) {
	std::thread t1(sumVec, (size_t)0, v1.size()/2, cref(v1), cref(v2), ref(res));
	std::thread t2(sumVec, v1.size()/2, v1.size(), cref(v1), cref(v2), ref(res));
	t1.join();
	t2.join();
}
parallelSum(v1, v2, res);
```

