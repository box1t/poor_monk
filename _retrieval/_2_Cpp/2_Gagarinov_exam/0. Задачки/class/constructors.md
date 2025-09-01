
```c++
Задача. Есть ли проблемы в следующем классе, и если да, то какие и как их исправить?  
class String {  
	public:  
/*  
Предположим что основные конструкторы и деструктор написаны  
*/  
	String& operator=(const String& other) {  
		str_ = other.str_;  
	}  
	private:  
		char* str_ = nullptr;  
	};

/////////////////////


class String {
public:
    // Предположим, что основные конструкторы и деструктор написаны

    // Оператор присваивания
    String& operator=(const String& other) {
        // Проверка на самоприсваивание
        if (this != &other) {
            // Освобождение памяти, занятой текущей строкой
            delete[] str_;

            // Выделение памяти для новой строки
            str_ = new char[strlen(other.str_) + 1];

            // Копирование содержимого из other в str_
            strcpy(str_, other.str_);
        }
        // Возвращаем ссылку на текущий объект
        return *this;
    }

private:
    char* str_ = nullptr;
};

```


```c++

class Student {
public:
    // Копирующий конструктор
    Student(const Student& other) = default;
/*
Student(const Student& other): full_name_(other.full_name_), group_name_(other.group_name_), grade_(other.grade_) {}
*/


private:
    std::string full_name_;
    std::string group_name_;
    size_t grade_;
};

```

```
Как избежать копипасты в следующем коде?


class Student {
  public:
    explicit Student(std::string full_name): full_name_(full_name) {
        if (full_name_ == "гений") {
            grade_ = 10;
        }
    }
    
    Student(std::string full_name, std::string group_name): full_name_(full_name), group_name_(group_name) {
        if (full_name_ == "гений") {
            grade_ = 10;
        }
    }
    
    
  private:
    std::string full_name_;
    std::string group_name_;
    size_t grade_;
};
```


```cpp
#include <string>

class Student {
public:
    // Конструктор с одним параметром
    explicit Student(std::string full_name)
        : full_name_(full_name) {
        InitializeGrade();
    }

    // Конструктор с двумя параметрами
    Student(std::string full_name, std::string group_name)
        : full_name_(full_name), group_name_(group_name) {
        InitializeGrade();
    }

private:
    // Инициализация оценки
    void InitializeGrade() {
        if (full_name_ == "гений") {
            grade_ = 10;
        }
    }

    std::string full_name_;
    std::string group_name_;
    size_t grade_;
};
```


