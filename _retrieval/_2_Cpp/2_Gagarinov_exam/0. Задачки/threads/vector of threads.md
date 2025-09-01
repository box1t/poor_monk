```c++
std::vector<std::thread> threads;
for (int i = 0; i < 5; ++i) {
	threads.push_back(std::threads([](){
	std::cout << std::this_thread::get_id() << std::endl;
	}));
}

for (auto& thread : threads) {
	thread.join();
}
```


