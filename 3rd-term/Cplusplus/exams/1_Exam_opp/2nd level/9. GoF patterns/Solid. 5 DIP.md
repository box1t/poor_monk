25. SOLID: Dependency Inversion Principle.

Принцип инверсии зависимостей:

1. Модули верхнего уровня не должны зависеть от модулей нижнего уровня. Оба типа модулей должны зависеть от абстракций.
2. Абстракции не должны зависеть от деталей. Детали должны зависеть от абстракций.

Предположим, у нас есть класс `HighLevelModule`, который зависит от низкоуровневого модуля `LowLevelModule`:


```cpp
class LowLevel {
public:
    void action() {}
};

class HighLevel {
private:
    LowLevel lowLevel;
public:
    void action() {
        lowLevel.action();
    }
};
```

Следуя принципу DIP, мы должны инвертировать зависимость таким образом, чтобы класс `HighLevelModule` зависел от абстракции, а не от конкретной реализации `LowLevelModule`. Мы можем достичь этого, введя абстракцию через интерфейс:

```cpp
class AbstractInterface {
public:
    virtual void doSomething() = 0;
};

class LowLevel : public AbstractInterface {
public:
    void action() override {}
};

class AbstractInterface {
private:
    AbstractInterface& module;
public:
    HighLevel(AbstractInterface& interface) : module(obj) {}

    void action() {
        module.action();
    }
};
```

Это позволяет легко заменить `LowLevel` другой реализацией, не внося изменений в `HighLevel`. Таким образом, принцип инверсии зависимостей помогает создавать более гибкую и расширяемую архитектуру программы.
