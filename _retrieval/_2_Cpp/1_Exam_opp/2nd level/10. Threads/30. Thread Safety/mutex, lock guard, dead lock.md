30. Потокобезопасность. Реентерабельность. Race condition. Взаимное исключение. std::mutex и std::recursive_mutex. std::lock_guard и std::unique_lock. Реализация потокобезопасного стека. dead_lock. Просачивание данных за пределы lock_guard

## Потокобезопасность
Везде в документации термины _реентерабельность_ и _потокобезопасность_ используются для обозначения классов и функций для указания того, как они могут быть использованы в многопоточных приложениях:

- _Потокобезопасная_ функция может быть вызвана одновременно из разных потоков, даже когда вызовы используют разделяемые данные, поскольку все обращения к разделяемым данным упорядочены.
- _Реентерабельная_ функция также может быть вызвана одновременно из нескольких потоков, но только если каждый вызов использует свои собственные данные.

Таким образом, _потокобезопасная_ функция всегда _реентерабельна_, но _реентерабельная_ функция не всегда _потокобезопасна_.

В более широком смысле, класс называется _реентерабельным_, если его функции-члены могут быть безопасно вызваны из нескольких потоков, пока каждый поток использует свой _отдельный_ экземпляр класса. Класс является _потокобезопасным_, если его функции-члены могут быть безопасно вызваны из нескольких потоков, даже если все потоки используют _один_

- Класс реентрабелен, если его функции-члены могут быть безопасно вызваны из нескольких потоков, пока каждый поток использует свой отдельный экземпляр класса.

- Класс потокобезопасен, если его функции могут быть безопасно вызваны из нескольких потоков, даже если все потоки используют один экземпляр класса.


```c++
#include <iostream>
#include <thread>
#include <mutex>

class some_data
{
public:
	void do_something() const
	{
		std::cout << "Computatation" << std::endl;
	};
};

class data_wrapper
{
private:
        // защищенные данные, к которым ограничен доступ из разных потоков
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> l(m);
		std::cout << "Start protected call" << std::endl;
		func(data); 
		std::cout << "End protected call" << std::endl;
	}
};

some_data* unprotected;

// Функция, которую хотим сделать потокобезопасной
void malicious_function(const some_data& protected_data)
{
	protected_data.do_something();
	unprotected = (some_data*)&protected_data;
}


int main()
{
	data_wrapper x;
        
	x.process_data<void (const some_data& protected_data)>(malicious_function);
	
	
	unprotected->do_something();
}
```

## Реентерабельность


## Race condition


## Взаимное исключение



## std::mutex и std::recursive_mutex

- std::mutex - Стандартный мьютекс, имеющий методы lock и unlock.
Предоставляет дополнительный неблокирующий метод try_lock
- std::recursive_mutex - Аналогичен классу mutex, но если поток заблокирует экземпляр
этого класса, то может заблокировать один мьютекс несколько раз
без блокировки. Данный мьютекс будет освобожден после того, как
обладающий им поток вызовет метод unlock столько раз, сколько раз
он вызвал метод lock



## std::lock_guard и std::unique_lock

Для управления памятью существуют вспомогательные классы unique_ptr,
shared_ptr и weak_ptr. Они предоставляют очень удобный способ избежать утечек
памяти. Такие классы существуют и для мьютексов. Простейшим из них является
std::lock_guard. Его можно использовать следующим образом:

```c++
void critical_function() {
	lock_guard<mutex> l {some_mutex};
	// критический раздел
}
```
Конструктор элемента lock_guard принимает мьютекс, для которого мгновенно
вызывает метод lock. Весь вызов конструктора заблокируется до тех пор, пока тот
не получит блокировку для мьютекса. При разрушении объекта он разблокирует
мьютекс. Таким образом, понять цикл блокировки/разблокировки сложно, по-
скольку она происходит автоматически

- lock_guard - Предоставляет только конструктор и деструктор, которые блокируют
и разблокируют мьютекс
- unique lock - Блокирует мьютекс в эксклюзивном режиме. Конструктор также
принимает аргументы, которые указывают ему сделать тайм-аут
вместо постоянной блокировки. Можно и вовсе не блокировать
мьютекс или предположить, что он был уже заблокирован, или только
попытаться заблокировать мьютекс. Дополнительные методы позволяют
заблокировать и разблокировать мьютекс во время существования
блокировки unique_lock


Тип блокировщика std::unique_lock превосходит возможностями своего
младшего брата std::lock_guard, но и обходится дороже. В дополнение к воз-
можностям, которые предоставляет тип std::lock_guard, тип std::unique_lock
позволяет также:
•• создавать блокировщик, не связанный с каким-либо мьютексом;
•• создавать блокировщик, не блокируя переданный ему мьютекс;
•• в явном виде многократно захватывать и освобождать мьютекс;
•• запирать мьютекс рекурсивно;
•• перемещать мьютекс в другой блокировщик;
•• пытаться захватить мьютекс2;
•• задавать предельное время ожидания при попытке захвата мьютекса.

### std::unique_lock

Класс `unique_lock` — это универсальная оболочка владения мьютексом, предоставляющая отсроченную блокировку, ограниченные по времени попытки блокировки, рекурсивную блокировку, передачу владения блокировкой и использование с `condition variables`.

Ограниченные по времени попытки блокировки работают так же, как и в классе `std::timed_mutex`. Для этого связанный мьютекс должен быть `TimedLockable`.

Отсроченная блокировка:

Класс `std::unique_lock` обеспечивает немного более гибкий подход, по сравнению с `std::lock_guard`: экземпляр `std::unique_lock` не всегда владеет связанным с ним мьютексом. Конструктору в качестве второго аргумента можно передавать не только объект `std::adopt_lock`, заставляющий объект блокировки управлять блокировкой мьютекса, но и объект отсрочки блокировки `std::defer_lock`, показывающий, что мьютекс при конструировании должен оставаться разблокированным. Блокировку можно установить позже, вызвав функцию `lock()` для объекта `std::unique_lock` (но не мьютекса) или же передав объект `std::unique_lock` функции `std::lock()`.

`std::unique_lock` занимает немного больше памяти и работает несколько медленнее по сравнению с `std::lock_guard`. За гибкость, заключающуюся в разрешении экземпляру `std::unique_lock` не владеть мьютексом, приходится расплачиваться тем, что информация о состоянии должна храниться, обновляться и проверяться: если экземпляр действительно владеет мьютексом, деструктор должен вызвать функцию unlock(), в ином случае — не должен. Этот флаг можно запросить, вызвав метод `owns_lock()`. Если передача владения блокировкой или какие-то другие действия, требующие `std::unique_lock`, не предусматриваются, лучше воспользоваться классом `std::scoped_lock` из C++17.


### std::condition_variable

Класс `condition_variable` — это примитив синхронизации, который может использоваться для блокировки потока или нескольких потоков до тех пор, пока другой поток не изменит общую переменную (не выполнит условие) и не уведомит об этом `condition_variable`.

Поток, который намеревается изменить общую переменную, должен:

- захватить `std::mutex` (обычно через `std::lock_guard`)
    
- выполнить модификацию, пока удерживается блокировка мьютекса
    
- выполнить `notify_one` или `notify_all` на `std::condition_variable` (блокировка не должна удерживаться для уведомления)
    

Даже если общая переменная является атомарной, всё равно требуется использовать мьютекс для корректного оповещения ожидающих потоков.

Любой поток, который ожидает наступления события от `std::condition_variable`, должен:

- С помощью `std::unique_lock<std::mutex>` получить блокировку того же мьютекса, который используется для защиты общей переменной.
    
- Проверить, что необходимое условие ещё не выпонлено.
    
- Вызвать метод wait, wait_for или wait_until. Операции ожидания освобождают мьютекс и приостанавливают выполнение потока.
    
- Когда получено уведомление, истёк тайм-аут или произошло ложное пробуждение, поток пробуждается, и мьютекс повторно блокируется. Затем поток должен проверить, что условие, действительно, выполнено, и возобновить ожидание, если пробуждение было ложным.
    

Вместо трёх последних шагов можно воспользоваться перегрузкой методов wait, wait_for и wait_until, которая принимает предикат для проверки условия и выполняет три последних шага.

`std::condition_variable` работает только с `std::unique_lock<std::mutex>`; это ограничение обеспечивает максимальную эффективность на некоторых платформах. `std::condition_variable_any` работает с любым BasicLockable объектом, например, с `std::shared_lock`.

Condition variables допускают одновременный вызов методов wait, wait_for, wait_until, notify_one и notify_all из разных потоков.

```c++
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <conditional_variable>

std::mutex m;
std::conditional_variable cv;
std::string data;
bool ready = false;
bool processed = true;

void worker_thread() {
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk, []{return ready;});

	std::cout << "Worker thread is processing data\n";
	data += "after processing";
	processed = true;
	std::cout << "worker thread signals data processing completed\n";
	lk.unlock();
	cv.notify_one();
}
int main() {
	std::thread worker(worker_thread);
	data = "Example data";
	{
		std::lock_guard<std::mutex> lk(m);
		ready = true;
		std::cout << "main() signals data ready for processing";
	}
	cv.notify_one();
	{
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk,[]{return processed;});
	}
	std::cout << "Back in main(), data = " << data << "\n";
	worker.join();
}
```


## Реализация потокобезопасного стека

```c++
#include <iostream>
#include <thread>
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
#include <vector>
#include <sstream>



class empty_stack : std::exception{
};


struct print : std::stringstream{
    ~print(){
        static std::mutex mtx;
        std::lock_guard<std::mutex> lck(mtx);
        std::cout << this->str();
        std::cout.flush();
    }
};

template <typename T>
class thread_safe_stack
{
private:
    std::stack<T> data;
    mutable std::mutex m;

public:
    thread_safe_stack(void){};

    thread_safe_stack(const thread_safe_stack &other){
        std::lock_guard<std::mutex> lock(other.m);
        data = other.data;
    };

    void push(T new_value){
        std::lock_guard<std::mutex> lock(m); // try to comment
        data.push(new_value);
    }

    std::shared_ptr<T> pop(){
        std::lock_guard<std::mutex> lock(m);
        if (data.empty())
            throw empty_stack();
        std::shared_ptr<T> const res(new T(data.top()));
        data.pop();
        return res;
    }

    void pop(T &value){
        std::lock_guard<std::mutex> lock(m); // try to comment
        if (data.empty())
            throw empty_stack();
        value = data.top();
        data.pop();
    }

    bool empty() const{
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
};

void foo(thread_safe_stack<std::string> *stack, int number)
{
    for (int i = 0; i < 1000; i++)
        stack->push(std::string("some string"));
    try{
        for (int i = 0; i < 1000; i++){
            std::string val;
            stack->pop(val);
        }
    }
    catch (...){
        print() << "Oppps!" << std::endl;
    }

    print() << "Thread " << number << (stack->empty() ? " is empty" : " is not empty") << "\n";
}

int main(int argc, char *argv[]){
    thread_safe_stack<std::string> stack;
    std::vector<std::thread> threads;

    for (int i = 0; i < 100; i++)
        threads.push_back(std::thread(foo, &stack, i));

    for (auto &tt : threads)
        tt.join();
    
    print() << "Done \n";

    return 0;
}
```


## dead_lock



## Просачивание данных за пределы lock_guard




## Управление потоками

Состояние гонок - ошибка проектирования многпоточной системы, когда работа приложения зависит от того, в каком порядке выполняются части кода. Состояние гонки возникает, кода несколько поток пытаются получить доступ к данным, причем хотя бы один поток уже выполняет запись. Для предотвращения данной ошибки применяются приемы синхронизации структур данных.

## Переключение контекста потоков

Чтобы операционная система поддерживала многозадачность, каждый выполняемый поток должен обладать своим контекстом исполнения. Этот контекст используется для хранения данных о текущем состоянии потока: значения регистров процессора, указателя на стек данных, указатель на текущую выполняемую команду.

Переключение контекста:

- обновляется контекст текущего потока
- из имеющихся потоков в ОС выбирается один, который будет исполняться на процессоре
- загружается контекст выбранного потока

### [](#stdthread)std::thread

Создание объекта типа std::thread запускает новый поток.

```
#include <iostream>
#include <thread>

void hello() {
  std::cout << "Hello, World!";
}

int main() {
  std::thread th(hello);
  th.join();
}
```

До вызова деструктора объекта типа std::thread необходимо вызвать или метод join(), или метод detach(). Вызов метода join приведет к ожиданию завершения потока. Это значит, что до тех пор пока поток не завершит своё выполнение, основной поток не будет выполнять код находящийся после вызова метода join(). Этот метод необходимо использовать, если основному потоку необходим и важен результат выполнения дочернего потока. Например, когда необходимо дождаться загрузки данных для дальнейшей обработки этих данных. Вызов функции detach оставляет поток работать в фоновом режиме. Это значит, что код находящийся после вызова метода detach() может выполняться пока выполняется запущенный поток. Этот метод необходимо использовать, если основному потоку не важен результат выполнения дочернего потока. Например, отправка пользовательской статистики. Класс std::thread является перемещающимся типом со всеми вытекающими последствиями.


## Синхронизация потоков

Для избежания состояния гонки следует синхронизировать потоки. Простейшим способом синхронизации потоков является взаимоисключающая блокировка. Класс mutex является примитивом синхронизации, который может использоваться для защиты разделяемых данных от одновременного доступа нескольких потоков. Mutex предлагает эксклюзивую, нерекурсивную семантику владения:

- Вызывающий поток владеет мьютексом со времени успешного вызова lock или try_lock, и до момента вызова unlock.
- Пока поток владеет мьютексом, все остальные потоки при попытке завладения им блокируются на вызове lock или получают значение false при вызове try_lock.
- Вызывающий поток не должен владеть мьютексом до вызова lock или try_lock.

Поведение программы не определено, если занятый некоторым потоком мьютекс разрушается или поток завершает работу и не освободил мьютекс.

### [](#lock_guard)lock_guard

std::lock_guard класс. является оболочкой для mutex и позволяет реализовать идиому RAII в его отношении. Когда создается объект lock_guard, он завладевает мьютексом и исвобождает его либо при вызове декструктора, либо при вызове `unlock()`

```
void safe_increment()
{
    const std::lock_guard<std::mutex> lock(g_i_mutex);
    ++g_i;

    std::cout << std::this_thread::get_id() << ": " << g_i << '\n';

    // g_i_mutex is automatically released when lock
    // goes out of scope
}
```

### [](#unique_lock)unique_lock

Является аналогом lock_guard, но при этом является перемещаемым и обладает набором вспомогательных метдов. Например `try_lock`

Пример:

```
struct Box {
    explicit Box(int num) : num_things{num} {}

    int num_things;
    std::mutex m;
};

void transfer(Box &from, Box &to, int num)
{
    // don't actually take the locks yet
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);

    // lock both unique_locks without deadlock
    std::lock(lock1, lock2);

    from.num_things -= num;
    to.num_things += num;

    // 'from.m' and 'to.m' mutexes unlocked in 'unique_lock' dtors
}

int main()
{
    Box acc1(100);
    Box acc2(50);

    std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
    std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);

    t1.join();
    t2.join();
}
```

### [](#recursive_mutex)recursive_mutex

Данный класс помагает избежать взаимных блокировок, так как он позволяет получать самого себя несколько раз.

```
template <typename T>
class container
{
     std::mutex _lock;
     std::vector<T> _elements;
public:
     void add(T element)
     {
          _lock.lock();
          _elements.push_back(element);
          _lock.unlock();
     }
     void addrange(int num, ...)
     {
          va_list arguments;
          va_start(arguments, num);
          for (int i = 0; i < num; i++)
          {
               _lock.lock();
               add(va_arg(arguments, T));
               _lock.unlock();
          }
          va_end(arguments);
     }
     void dump()
     {
          _lock.lock();
          for(auto e: _elements)
          std::cout << e << std::endl;
          _lock.unlock();
     }
};

void threadFunction(container<int> &c)
{
     c.addrange(3, rand(), rand(), rand());
}

int main()
{
     srand((unsigned int)time(0));
     container<int> cntr;
     std::thread t1(threadFunction, std::ref(cntr));
     std::thread t2(threadFunction, std::ref(cntr));
     std::thread t3(threadFunction, std::ref(cntr));
     t1.join();
     t2.join();
     t3.join();
     cntr.dump();
     return 0;
}
```

### [](#shared_mutex)shared_mutex

shared_mutex – это мьютекс позволяющий одновременно многим потокам читать одни и те же данные, если в этот момент нет потоков изменяющих эти данные.


