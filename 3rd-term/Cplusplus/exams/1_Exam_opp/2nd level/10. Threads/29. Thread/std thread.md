29. std::thread. Функции и функторы как параметры. Использование семантики перемещения в std::thread. Функциии из пространства имен std::this_thread. Идиома RAII и std::thread.


## std::thread



## Функции и функторы как параметры



## Использование семантики перемещения в std::thread



## Функциии из пространства имен std::this_thread

| Defined in namespace `this_thread`                                                           |                                                                         |
| -------------------------------------------------------------------------------------------- | ----------------------------------------------------------------------- |
| [yield](https://en.cppreference.com/w/cpp/thread/yield "cpp/thread/yield")                   | suggests that the implementation reschedule execution of threads  <br>  |
| [get_id](https://en.cppreference.com/w/cpp/thread/get_id "cpp/thread/get id")<br>            | returns the thread id of the current thread                             |
| [sleep_for](https://en.cppreference.com/w/cpp/thread/sleep_for "cpp/thread/sleep for")       | stops the execution of the current thread for a specified time duration |
| [sleep_until](https://en.cppreference.com/w/cpp/thread/sleep_until "cpp/thread/sleep until") | stops the execution of the current thread until a specified time point  |
|                                                                                              |                                                                         |
|                                                                                              |                                                                         |

// 1. Provides a hint to the implementation to reschedule the execution of threads, allowing other threads to run.

The exact behavior of this function depends on the implementation, in particular on the mechanics of the OS scheduler in use and the state of the system. For example, a first-in-first-out realtime scheduler (`SCHED_FIFO` in Linux) would suspend the current thread and put it on the back of the queue of the same-priority threads that are ready to run (and if there are no other threads at the same priority, `yield` has no effect).

```

#include <chrono>
#include <iostream>
#include <thread>
 
// "busy sleep" while suggesting that other threads run 
// for a small amount of time
void little_sleep(std::chrono::microseconds us)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    do
    {
        std::this_thread::yield();
    }
    while (std::chrono::high_resolution_clock::now() < end);
}
 
int main()
{
    auto start = std::chrono::high_resolution_clock::now();
 
    little_sleep(std::chrono::microseconds(100));
 
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "waited for "
              << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
              << " microseconds\n";
}

```
// 2. Returns the _id_ of the current thread.

```
std::thread::id this_id = std::this_thread::get_id();
std::osyncstream(std::cout) << "thread: " << this_id << "sleeping...\n";
std::this_thread::sleep_for(500ms);
```

// 3 std::this_thread::sleep_for
Blocks the execution of the current thread for _at least_ the specified sleep_duration.

This function may block for longer than sleep_duration due to scheduling or resource contention delays.

The standard recommends that a steady clock is used to measure the duration. If an implementation uses a system clock instead, the wait time may also be sensitive to clock adjustments.

```c++
#include <chrono>
#include <iostream>
#include <thread>
 
int main()
{
    using namespace std::chrono_literals;
 
    std::cout << "Hello waiter\n" << std::flush;
 
    const auto start = std::chrono::high_resolution_clock::now();
    std::this_thread::sleep_for(2000ms);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = end - start;
 
    std::cout << "Waited " << elapsed << '\n';
}
```



## Идиома RAII и std::thread

