

```c++
// with mistake

#include <iostream>

class Complex {
private:
    double real, imag;
public:
    // Конструктор по умолчанию
    Complex() : real(0.0), imag(0.0) {}

    // Конструктор с параметрами
    Complex(double real, double imag) : real(real), imag(imag) {}
    
    // Конструктор копирования
    Complex(const Complex& other) {
        real = other.real;
        imag = other.imag;
    }
    
    // Конструктор перемещения
    Complex(Complex&& other) noexcept {
        real = std::move(other.real);
        imag = std::move(other.imag);
    }
    
    // Оператор копирования
    Complex& operator=(const Complex& other) {
        if(this!=&other) {
            real = other.real;
            imag = other.real;
        }
        return *this;
    }
    
    // Оператор присваивания (перемещения)
    Complex& operator=(Complex&& other) noexcept {
        if(this!=&other) {
            real = std::move(other.real);
            imag = std::move(other.imag);
            //other.real = 0;
            //other.imag = 0;
        }
        return *this;
    }

	//Complex operator+=(const Complex& other) {

    // Перегрузка оператора сложения
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Вывод комплексного числа
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.real << " + " << c.imag << "i";
        return os;
    }
};

```

```c++
class Complex {
private:
	double re, image;
public:
	Complex(double re, double image) : re(re), image(image) {}
	Complex(const Complex& other)
	Complex& operator=()
	Complex(Complex&& other)
	Complex& operator=(Complex&& other)

	Complex& operator+=

};

Complex& operator+()
```