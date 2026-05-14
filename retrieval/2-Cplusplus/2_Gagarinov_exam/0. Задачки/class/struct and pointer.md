```c++
#include <iostream>

// Объявление шаблонного класса для определения, является ли тип указателем
template<typename T>
struct IsPointer {
    static constexpr bool value = false;
};

// Специализация шаблона для определения, является ли тип указателем
template<typename T>
struct IsPointer<T*> {
    static constexpr bool value = true;
};

int main() {
    std::cout << std::boolalpha;
    std::cout << "Is int* a pointer? " << IsPointer<int*>::value << std::endl;
    std::cout << "Is float a pointer? " << IsPointer<float>::value << std::endl;

    return 0;
}

```

