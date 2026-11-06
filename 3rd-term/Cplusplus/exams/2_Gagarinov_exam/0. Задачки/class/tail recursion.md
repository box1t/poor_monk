```c++
##### ust for fun: compile-time факториал

Теперь мы разбираемся в шаблонах достаточно чтобы посчитать факториал во время компиляции на шаблонах (разобрать пример, показать результат в godbolt).

Примечание: C++ значительно эволюционировал, и больше во время компиляции таким образом вычисления не проводят. Пример исключительно ученический. Compile-time вычисления будут рассмотрены в курсе далее.

template<unsigned N>
struct Factorial
{
    static const int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0>
{
    static const int value = 1;
};

int main()
{
    return Factorial<10>::value;
}
```

```c++
#include <cstdio>

template<unsigned N>
struct f
{
    static const int value = f<N-1>::value + f<N-2>::value;
};

template<>
struct f<0>
{
    static const int value = 0;
};

template<>
struct f<1>
{
    static const int value = 1;
};

int main()
{
    printf("%i\n", f<45>::value);
}
```