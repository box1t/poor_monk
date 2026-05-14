
```c++
#include <iostream>

class Square {
private:
    double side;

public:
    Square(double s) : side(s) {}

    // Конструктор копирования
    Square(const Square& other) : side(other.side) {}

    // Оператор присваивания копированием
    Square& operator=(const Square& other) {
        if (this != &other) {
            side = other.side;
        }
        return *this;
    }

    // Конструктор перемещения
    Square(Square&& other) noexcept : side(std::move(other.side)) {}

    // Оператор присваивания перемещением
    Square& operator=(Square&& other) noexcept {
        if (this != &other) {
            side = std::move(other.side);
        }
        return *this;
    }

    // Перегруженный оператор сложения сторон
    Square operator+(const Square& other) const {
        return Square(side + other.side);
    }

    // Метод для вывода в консоль
    friend std::ostream& operator<<(std::ostream& os, const Square& box) {
        os<<"Side a box = "<<box.side;
        return os;
    }
};

```

