# Task 1

```c++
(2) Рассмотрим следующую программу (считаем, что все необходимые заголовочные файлы подключены):  
union S {  
    std::string str;    
    std::vector<int> vec;    
    ~S() {}  
};  
int main() {    
	S s = {"Hello, world"};    
	new (&s.vec) std::vector<int>;    
	s.vec.push_back(10);    
	std::cout << s.str.size() << ' ' << s.vec.size() << '\n';  
}  
Корректен ли этот код? Если нет, объясните, какие потенциальные проблемы он содержит и почему.
```


# Task 2

```c++
(2) Пусть есть класс:  
class TreeNode {  
   int x;  
   std::string s;  
   TreeNode *parent, *leftChild, *rightChild;  
   // ...   // some methods  
};  
Определите для данного класса конструктор перемещения и перемещающий оператор присваивания так, чтобы move-семантика корректно поддерживалась.
```

```c++
class TreeNode{
private:
	int x;
	std::string s;
	TreeNode *parent, *leftChild, *rightChild;
public:
	TreeNode(TreeNode&& other) : {}
	TreeNode& operator=(TreeNode&& other) {
		
	}

};



```


# Task 3

```c++
(2) Вы пишете шаблонный класс TalkativeAllocator<T>, который ведет себя аналогично std::allocator, с той разницей, что выводит на экран сообщения обо всех своих действиях. Не используя сущностей из заголовочного файла <memory>, определите метод TalkativeAllocator<T>::construct. (Он должен принимать то же, что и std::allocator<T>::construct, и делать то же самое, что и упомянутый метод, но предварительно выводить на экран сообщение “Construct method has been called!”.)
```

```c++
template <class T>
class TalkativeAllocator {

};
```

# Task 4

```c++
(2) Для чего нужна функция std::make_shared, что она принимает и что возвращает? Почему использование этой функции в С++14 предпочтительнее, чем непосредственный вызов конструктора shared_ptr?
```



# Task 5

```c++
(2) Рассмотрим следующую программу (подразумевается, что все необходимые заголовочные файлы подключены):  
int main() {  
   std::vector<std::unique_ptr<int>> vec;  
   vec.reserve(10000);  
   for (int i = 0; i < 10000; ++i) {  
       vec.push_back(std::make_unique<int>(new int(rand())));  
   }  
   auto cmp = [](auto x, auto y){return *x < *y;};  
   std::sort(vec.begin(), vec.end(), cmp);  
}  
Скомпилируется ли она? Если нет, то в каких строчках возникнут ошибки компиляции и почему? Если да, то какие потенциальные проблемы она в себе содержит (undefined behaviour, утечки памяти и т.п.) и почему?
```


# Task 6

```c++
(2) Зачем нужен класс std::enable_shared_from_this? Приведите пример ситуации, когда его нужно использовать.
```


# Task 7

```c++
(2) Рассмотрим следующую программу:  
#include <iostream>  
class FunctionCreater {  
private:  
    int divisor;  
public:  
    FunctionCreater(int divisor): divisor(divisor) {}  
    std::function<int(int)> getFunction() const {  
        auto func = [=](int x){return x % divisor;};  
        return func;  
    }  
};  
int main() {  
    auto f = FunctionCreater(5).getFunction();  
    auto g = FunctionCreater(10).getFunction();  
    std::cout << f(15) << ‘ ‘ << g(15);  
}  
Какую потенциальную проблему она содержит? Почему так происходит? Как нужно исправить код getFunction, чтобы возвращаемая функция работала корректно?
```


# Task 8

```c++
(2) Зачем нужен оператор noexcept? В чем разница между ним и одноименным спецификатором? Приведите пример его применения.
```

# Task 9

```c++
(2) Рассмотрим такой оператор сложения двух длинных чисел:  
BigInteger operator +(const BigInteger& a, const BigInteger& b) {  
   BigInteger sum = a;  
   sum += b;  
   return sum;  
}  
Имеет ли смысл написать вместо “return sum” “return std::move(sum)”? Аргументируйте свой ответ.
```


# Task 10

```c++
(2) Объявите и определите лямбда-функцию, которая захватывает перемещением локальный std::vector<int> (назовем его vec), сортирует его стандартным способом и выводит содержимое получившегося вектора в cout. Для удобства можно считать, что все необходимые заголовочные файлы уже подключены.
```

# Task 11

```c++
(2) Напишите шаблонный класс Fibonacci<int N> с полем static const long long value, значение которого для каждой специализации с конкретным N равнялось бы N-му числу Фибоначчи, при условии, что это число не превышает максимальное значение типа long long. (Для удобства считаем, что глубина шаблонной рекурсии ничем не ограничена.)
```




