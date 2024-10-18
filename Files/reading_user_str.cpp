#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> lines;  // Вектор для хранения строк
    std::string input;

    std::cout << "Введите строки (введите 'end', чтобы завершить ввод):" << std::endl;

    while (true) {
        std::getline(std::cin, input);  
        if (input == "end") {           
            break;
        }
        lines.push_back(input);
    }

    std::cout << "\nВы ввели следующие строки:\n" << std::endl;

    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }

    return 0;
}

/*
Чтение строк от пользователя:

1) Получаем строку от пользователя
2) Условие для завершения ввода
3) Добавляем строку в вектор
4) Вывод всех введённых строк

*/



while (true) {
    std::getline(std::cin, input);
    if (input == "end") {
        lines.push_back(input);
        break;
    }
    for (const auto& line : lines) {
        std::cout << line << std::endl;
    }
}

