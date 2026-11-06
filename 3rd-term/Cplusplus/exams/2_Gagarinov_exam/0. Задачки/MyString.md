Объект класса - конкретный элемент этого типа.
Класс-наследник **уточняет** характеристики базового класса

## Task1. RAII

##### RAII (Resource Acqusition Is Initialization)

RAII - ключевая идиома в С++: захват ресурса должен совпадать с инициализацией объекта, а освобождение ресурса с его разрушением.

Т.о.:

- конструктор объекта захватывает ресурс
- деструктор объекта его освобождает

```c++
**Пример 1**: массив на куче

class ArrayD
{
private:
    double* data;
    int size;
    
public:
    ArrayD(int n)
        : data(new double[n]),
        , size(n)
    {
    }
    
    ~ArrayD()
    {
        delete[] data;
    }    
};
```


## Task 3. MyString

```c++
##### Мой первый класс

Реализуем класс - строку на С++.

Важнейший принцип языка, основа его основ - RAII (Resource Acquisition Is Initialization)

class String
{
public:
    String();
    String(const char *s);
    String(const char *s, int size);
    ~String();
    String(const String& rhs);
    String(String&& rhs);

    String& operator = (const String& rhs);
    String& operator = (String&& rhs);

    friend String operator + (const String& lhs, const String& rhs);

private:
    char* s_;  // pointer to null-terminated characters
    size_t l_; // strlen(s_) == l_
};
```

```c++
Для начала реализуем оператор сложения двух строк

String operator + (const String& lhs, const String& rhs)
{
    const size_t res_size = lhs.l_ + rhs.l_;
    const char* res_s = new char[res_size + 1];
    strcpy(res_s, lhs.s_);
    strncpy(res_s + lhs.l_, rhs.s_, rhs.l_);
    
    String s(res_s, res_size);

    delete[] res_s;
    return s;
}
```

```c++
**конструкторы** - код, вызываемый при создании объекта

String::String()
    : s_(new char[1])
    , l_(0)
{
    s_[0] = 0;
}

String::String(const char* s)
{
    l_ = strlen(s);
    s_ = new char[l + 1];
    strcpy(s_, s);
}

String::String(const char *s, int size)
    : s_(new char[size + 1])
    , l_(size + 1)
{
    strncpy(s_, s, size);
    s_[l_] = 0;
}

**деструктор** - код, который будет вызываться при уничтожении объекта

String::~String()
{
    delete[] s_;
}
```

```c++
Остановимся на секунду и всомним про RAII

**конструктор копирования**

String::String(const String& rhs)
{
    s_ = new char[rhs.l_ + 1];
    l_ = rhs.l_;
    strcpy(s_, rhs.s_);
}

Правильный конструктор перемещения

String::String(String&& rhs)
{
    s_ = rhs.s_;
    l_ = rhs.l_;

    rhs.s_ = new char[1];
    rhs.s_[0] = 0;
    rhs.l_ = 0;
}
```



**копирующее присваивание**

```c++
**копирующее присваивание**

String& String::operator =(const String& rhs)
{
    s_ = new char[rhs.l_ + 1];
    l_ = rhs.l_;
    strcpy(s_, rhs.s_);

    return *this;
}

Где ошибка?

Утекает предыдущий массив `s_`

String& String::operator =(const String& rhs)
{
    delete[] s_;

    s_ = new char[rhs.l_ + 1];
    l_ = rhs.l_;
    strcpy(s_, rhs.s_);

    return *this;
}

Где ошибка?

Самоприсваивание

Правильная реализация будет выглядеть так:

String& String::operator =(const String& rhs)
{
    if (this != &rhs)
    {
        delete[] s_;

        s_ = new char[rhs.l_ + 1];
        l_ = rhs.l_;
        strcpy(s_, rhs.s_);
    }
    return *this;
}
```


**перемещающее присваивание**:
```c++
**перемещающее присваивание**:

**Вариант 1:** с очисткой `rhs`

String& String::operator =(String&& rhs)
{
    if (this != &rhs)
    {
        delete[] s_;

        s_ = rhs.s_;
        l_ = rhs.l_;

        rhs.s_ = new char[1];
        rhs.s_[0] = 0;
        rhs.l_ = 0;
    }

    return *this;
}

**Вариант 2:** обмен с `rhs`

String& String::operator =(String&& rhs)
{
    std::swap(s_, rhs.s_);
    std::swap(l_, rhs.l_);
    return *this;
}
```

