


```c++
#include <iostream>
class MyFunction {
private:
    int m_x, m_y;
public:
    MyFunction(int x, int y) : m_x(x), m_y(y) {}
    void displayValues() const {
        std::cout << "x: " << m_x << ", y: " << m_y << std::endl;
    }
    int operator()() const {
        return m_x + m_y;
    }
};
int main() {
    MyFunction adder(3, 4); 
    adder.displayValues(); 
    std::cout << "Сумма: " << adder() << std::endl; 
    return 0;
}
```



