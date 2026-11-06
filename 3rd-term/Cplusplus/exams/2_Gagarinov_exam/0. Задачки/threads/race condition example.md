# Пример 1

```c++
void hello() {
	std::cout << "Hello world" << std::this_thred::get_id() << std::endl;
}

int main() {
	std::vector<std::thread> threads;
	for (int i = 0; i < 5; ++i) {
		threads.push_back(std::thread(hello));
	}
	for (auto& thread : threads) {
		thread.join();
	}
	return 0;
}

// для исправления нужен mutex and lock_guard
```



из-за переключения контекста и одновременной работы нескольких процессоров строчки
могли вклиниться друг в друга и превратиться в бессмысленный набор слов.

# Пример 2

```c++
struct Counter {
	int value;
	Counter() : value(0) {}
	void increment() {
		++value;
	}
};

int main() {
	Counter counter;
	std::vector<std::thread> threads;
	for (int i = 0; i < 5; ++i) {
		threads.push_back(thread([&](){
			for (int i = 0; i < 100; ++i) {
				counter.increment();
			}
		}
	))};

	for (auto& thread : threads) {
		thread.join();
	}

	std::cout << counter.value << std::endl;
}
```



Мы ожидаем, что выведется 500, однако, запустив это много раз, мы видим, что результат
меняется (причем кардинально) от запуска к запуску. Почему так происходит?
Допустим первый поток прочитал значение счетчика, оно равно 0.
Сразу после этого второй поток тоже прочитал и тоже получил 0.
Затем первый поток увеличил значение и записал туда 1.
Второй поток сделал то же самое и тоже записал туда 1.
В результате счетчик увеличислся не на 2, как ожидалось, а только на 1.


Для исправления ситуации используем mutex and lock_guard


```c++
struct Counter {
	std::mutex mtx;
	int value;
	Counter() : value(0) {}
	void increment() {
		std::lock_guard<std::mutex> lg(mtx);
		++value;
	}
};
```
