

Иногда хочется нестандартного выделения памяти.

Предположим, приложение потребляет не более 4 гб оперативы.
Использование типичных new delete затратно.

Мы можем выделить куски памяти и потом ее менеджерить.
Первый шаг к этому - научиться перегрузке new/delete



```c++
struct S {
	int x = 0;	
};

int main() {
	S* ptr = new S(); // 1
}

Как мы знаем, в строке 1 должна выделиться память.
Вызовется конструктор по умолчанию.
Перегрузить можно только шаг с выделением памяти.
Повлиять на конструктор не можем.
Это системная штука.


new - оператор, поэтому его можно перегрузить.
```


```c++
void* operator new(size_t n) {
	std::cout << "We are in new" << std::endl;
	return malloc(n);
}

void operator delete(void* p) noexcept {
	std::cout << "We are in delete" << std::endl;
	free(p);
}

struct S {
	int x=0;
};

int main() {
	S* ptr = new S();
	delete s;
}
``` 

```
void *operator new(size_t n) {
	std::cout << "We are in new" << std::endl;
	return malloc(n);
}
```

Оператор new возвращает воид * 
Это указатель, который может принять в себя что угодно.
Это просто какая-то память, и непонятно, что там лежит.

Принимает он количество байт, нужное к выделению.
В простом случае вызвали маллок.

Брат-близнец делет принимает указатель и вызывает free.


Существуют версии для массивов!
```c++
void* operator new[](size_t n) {
	std::cout << "We are in new []";
	return malloc(n);
}

void operator delete[](void* p) noexcept {
	std::cout << "We are in delete[]";
	free(p);
}
```
Логику [ ] берет на себя система. Ее мы тоже никак перегрузить не можем.

Убедимся, что перегрузки работают.

```c++
void* operator new(size_t n) {
	std::cout << "We are in new" << std::endl;
	return malloc(n);
}

void operator delete(void* p) noexcept {
	std::cout << "we are in delete" << std::endl;
	free(p);
}

int main() {
	std::vector<int> v(10);
	v[0] = 10;
}

// Вопреки тому что мы знаем, в векторе new[] не используется.
// в векторе используется стандартный оператор new
```

Версия СТЛ умеет кидать исключения, если выделить память не получилось.

```c++
void* operator new(size_t n) {
	std::cout << "we are in new" << std::endl;
	void* ptr = malloc(n);
	if (ptr == nullptr) {
		throw std::bad_alloc();
	}
	return ptr;
}
```

Перегрузка операторов для конкретного типа:

```c++
/*

Мы должны написать 2 статических оператора. 
Статик компилятор подставит и сам..


При выборе оператора для конкретного типа будет выбран тот, 
который объявлен внутри класса.

*/


struct S{
	static void* operator new(size_t n) {
		std::cout << "We are in new for S" << std::endl;
		void* ptr = malloc(n);
		if (ptr == nullptr) {
			throw std::bad_alloc();
		}
	return ptr;
	}
	static void operator delete(void* p) {
		std::cout << "We are in delete for S" << std::endl;
		free(p);
	}
};
```

***

# allocator

Это структура (всегда) шаблонная.
У нее есть 4 метода.

```c++
template <typename T>
struct Allocator {
	T* allocate(size_t n) {
		return ::operator new(n*sizeof(T));
	}
	void deallocate(T* ptr, size_t) {
		::operator delete(ptr);
	}
	template <typename... Args>
	void construct(T* ptr, const Args&...) { // in fact - Argc&&
		new(ptr) T(args...); // std::forward(args)
	} 
	void destroy(T* ptr) noexcept {
		ptr->~T();
	}
}
```

В с++20 construct and destroy убрали.
По большей части они одинаковы всегда.
Нас интересует allocate/deallocate

Никаких виртуальных функций тут нет, хотя аллокатор шаблонный.
А КАК БЛИН ВЫЗЫВАЮТСЯ МЕТОДЫ?
Почему это работает?

Обычно есть единый интерфейс.

Аллокатор как и new разделяет выделение памяти и вызов конструктора.


***
# Allocator traits

Большинство методов у всех аллокаторов одинаковые
(например, construct и destroy), а еще внутри куча using, поэтому в с++ была добавлена специальная обертка allocator traits.
allocator traits это структура, которая шаблонным параметром принимает класс вашего аллокатора.
почти все методы и внутренние юзинги работают по принципу "взять у аллокатора если есть, если нет - сгенерировать автоматически".


Трейтс дает унифицированный доступ к интерфейсу аллокатора.

если в аллокаторе нет функции констракт, он вызовет плейсмент нью.
(то же, что и стд аллокатор делает)

В трейст мы оборачиваем любой аллокатор, которым хотим пользоваться.
Потому что я не обязан писать в своем аллокаторе методы констракт и дестрой.

