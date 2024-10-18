#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> vec;
    std::string input_string;

    // Считываем строки до тех пор, пока пользователь не введет пустую строку
    while (std::getline(std::cin, input_string) && !input_string.empty()) {
        vec.push_back(input_string); // Добавляем считанную строку в вектор
    }

    // Конкатенируем строки из вектора
    std::string concatenated_string;
    for (const auto& str : vec) {
        concatenated_string += str;
    }

    // Выводим конкатенированную строку
    std::cout << "Concatenated string: " << concatenated_string << std::endl;

    return 0;
}



