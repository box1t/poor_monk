23. SOLID: Принцип подстановки Барбары Лисков.

Принцип подстановки Барбары Лисков гласит, что объекты должны быть заменяемыми на экземпляры их подтипов без изменения корректности программы. 


Предположим, у нас есть иерархия классов, где `Rectangle` является подтипом `Shape`, а `Square` - подтипом `Rectangle`.


```cpp
class Shape {
public:
    virtual int area() const = 0;
};

class Rectangle : public Shape {
protected:
    int width, height;
public:
	int area() const override { return width * height; }
	virtual void setWidth(int w) { width = w; }
    virtual void setHeight(int h) { height = h; }
};

class Square : public Rectangle {
public:
    void setWidth(int w) override { width = w; height = w; }
    void setHeight(int h) override { width = h; height = h; }
};
```

Если мы применяем объект `Square` в контексте, ожидающем объект типа `Rectangle`, программа не должна изменить своё поведение, так как `Square` является подтипом `Rectangle`. 
Но при передаче `Square`, который является подтипом `Rectangle`, результат вывода будет неверным. Это нарушает принцип подстановки Барбары Лисков.


Вместо этого оба класса должны быть прямыми наследниками `Shape`, что позволяет нам использовать любую фигуру в функции `processShape` без нарушения ожидаемого поведения. Теперь наша иерархия классов соблюдает принцип подстановки Барбары Лисков (LSP).

