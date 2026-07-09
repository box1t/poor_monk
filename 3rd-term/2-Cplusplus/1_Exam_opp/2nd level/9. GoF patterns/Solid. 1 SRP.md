21. SOLID: Принцип единой ответственности. Пример.

Принцип единой ответственности гласит, что класс должен иметь только одну причину для изменения. Другими словами, класс должен быть ответственен только за один аспект или функциональность системы.

Предположим, у нас есть класс `FileManager`, который управляет чтением и записью файлов, а также форматированием. Он нарушает принцип SRP, тк занимается слишком многими аспектами.

```cpp
class FileManager {
public:
    void readFile(const std::string& filename) {}
    void writeFile(const std::string& filename, const std::string& content) {}
    void formatContent(std::string& content) {}
};
```


Разделим класс на более мелкие. 

```cpp
class FileReader {
public:
    std::string readFile(const std::string& filename) {}
};

class FileWriter {
public:
    void writeFile(const std::string& filename, const std::string& content) {}
};

class ContentFormatter {
public:
    void formatContent(std::string& content) {}
};
```

Каждый класс отвечает только за свою конкретную задачу. 

Изменения логики работы с файлом будут затрагивать только соответствующий класс, не затрагивая другие части системы. 

