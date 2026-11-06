

```c++
// lambda version
#include <iostream>
#include <thread>
#include <stdexcept>


void exceptionHandler(std::exception_ptr& exPtr) {
    throw std::runtime_error("OOP");
}

void threadFoo(std::exception_ptr& exPtr) {
    std::thread t1([&exPtr]() { exceptionHandler(exPtr); });
    t1.join();
}

int main() {
    std::exception_ptr exPtr;
    threadFoo(exPtr);
    
    if (exPtr) {
        try {
            std::rethrow_exception(exPtr);
        } catch (const std::exception& ex) {
            std::cerr << ex.what() << std::endl;
        }
    }
    
    return 0;
}

```


Завести функцию, которая кинет исключения, в 10 разных потоков без создания гонки.

cout - неблокирующая операция.
нам не потребуется.

но...
функция прохождения опроса может быть положена в try catch

```c++
#include <iostream>
#include <vector>
#include <mutex>


void passSurvey(int numberOfStudents) {
	std::cout << numberOfStudents << " гениев прошли опрос." << std::endl;
	throw 
}

int main() {

	try {
		passSurvey(27);
	} catch(std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}

}
```


```c++
struct ReputationCounter {
	std::mutex mtx;
	short int karmaPoints;
	ReputationCounter() : karmaPoints(0) {}
	void increment() {
		std::lock_guard<std::mutex> locker(mtx);
		++karmaPoints;
	}
};



int main() {
	ReputationCounter karma;
	std::vector<std::thread> threads;
	
	for (int i = 0; i < 27; ++i) {
		threads.push_back(thread([&](){
			for (int i = 0; i < 100; ++i) {
				karma.increment();
			}
		}
	))};

	for (auto& thread : threads) {
		thread.join();
	}

	std::cout << karma.value << std::endl;
}
```

```c++
#include <iostream>

#include <mutex>

#include <thread>

#include <stdexcept>

#include <vector>

  
  

struct ReputationCounter {

std::mutex mtx;

short int karmaPoints;

ReputationCounter() : karmaPoints(0) {}

void increment() {

std::unique_lock<std::mutex> locker(mtx);

++karmaPoints;

}

};

  

void simpleAction(short int timesPassed) {

if (timesPassed == 5) {

throw std::runtime_error("сомнительно, но ОКЭЙ");

}

}

  

int main() {

  

try {

simpleAction(5);

}

catch(const std::exception& ex) {

std::cerr << ex.what() << std::endl;

}

  

ReputationCounter groupKarma;

std::vector<std::thread> threads;

short int studentsNumber = 25;

  

for (int i = 0; i < studentsNumber; ++i) {

threads.push_back(std::thread([&](){

groupKarma.increment();

}));

}

  

for (auto& thread : threads) {

thread.join();

}

  
  
  

std::cout << "Карма группы: " << groupKarma.karmaPoints << " из 27 очков." << std::endl;

std::cout << "Так держать!" << std::endl;

}
```

Программа не упала после try catch.
почему?

