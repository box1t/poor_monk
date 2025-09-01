

std::exception и std::exception_ptr. std::current_exception и std::rethrow_exception.


`std::exception` и `std::exception_ptr` являются частями исключительной модели C++, предназначенной для обработки ошибок и исключительных ситуаций в программе.

1. **std::exception**:
   `std::exception` является базовым классом для всех стандартных исключений в стандартной библиотеке C++. Он определен в заголовочном файле `<exception>`. Класс `std::exception` предоставляет метод `what()`, который возвращает C-style строку (типа `const char*`), описывающую исключительную ситуацию. Этот метод переопределяется в производных классах, чтобы предоставить специфическое описание ошибки.

Пример кода:

```cpp
#include <iostream>
#include <exception>

void someFunction() {
    try {
        // Некоторая логика, которая может бросить исключение
        throw std::runtime_error("An error occurred!");
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
}

int main() {
    someFunction();
    return 0;
}
```

2. **std::exception_ptr**:
   `std::exception_ptr` является объектом, который хранит указатель на объект типа `std::exception` или его производного класса. Он предназначен для передачи информации об исключении между различными частями программы, даже через границы потоков. `std::exception_ptr` обычно используется вместе с механизмом обработки исключений `std::promise`, `std::future`, `std::async`, `std::packaged_task` и другими.

Пример кода:

```cpp
#include <iostream>
#include <exception>
#include <future>

void someFunction(std::promise<int>& prom) {
    try {
        // Некоторая логика, которая может бросить исключение
        throw std::runtime_error("An error occurred!");
    } catch (...) {
        // Ловим любое исключение и передаем его в promise
        prom.set_exception(std::current_exception());
    }
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread t(someFunction, std::ref(prom));

    try {
        // Ждем результата или исключения
        fut.get();
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    t.join();
    return 0;
}
```

В этом примере `std::promise` используется для передачи исключения между потоками. `std::promise::set_exception()` используется для установки объекта `std::exception_ptr`, который может быть затем получен и обработан в основном потоке с помощью `std::future::get()`.


***

`std::current_exception` и `std::rethrow_exception` являются частями исключительной модели C++, предназначенной для обработки исключений и передачи информации об исключениях между различными частями программы.

1. **std::current_exception**:
   `std::current_exception` является функцией, которая возвращает объект `std::exception_ptr`, который содержит указатель на текущее исключение. Это позволяет сохранить текущее исключение и затем его повторно бросить или передать в другое место программы для обработки.

Пример использования:

```cpp
#include <iostream>
#include <exception>

void someFunction() {
    try {
        throw std::runtime_error("An error occurred!");
    } catch (...) {
        // Получаем указатель на текущее исключение
        std::exception_ptr exPtr = std::current_exception();

        // Обработка исключения
        // ...
    }
}

int main() {
    someFunction();
    return 0;
}
```

2. **std::rethrow_exception**:
   `std::rethrow_exception` - это функция, которая принимает объект `std::exception_ptr` и повторно бросает исключение, которое он хранит. Это позволяет повторно бросить исключение в другой части программы или в другом потоке.

Пример использования:

```cpp
#include <iostream>
#include <exception>

void someOtherFunction(std::exception_ptr exPtr) {
    try {
        // Повторно бросаем исключение
        std::rethrow_exception(exPtr);
    } catch (const std::exception& e) {
        // Обработка повторно брошенного исключения
        std::cerr << "Caught rethrown exception: " << e.what() << std::endl;
    }
}

void someFunction() {
    try {
        throw std::runtime_error("An error occurred!");
    } catch (...) {
        // Получаем указатель на текущее исключение
        std::exception_ptr exPtr = std::current_exception();

        // Передаем исключение в другую функцию для обработки
        someOtherFunction(exPtr);
    }
}

int main() {
    someFunction();
    return 0;
}
```

Эти функции позволяют эффективно передавать информацию об исключениях между различными частями программы, что может быть полезно для логирования, отладки и обработки ошибок.


