#include <iostream>
#include <string>
#include <unordered_map>

bool isIce(const std::string& other) {
    std::unordered_map<char, int> mapka;

    // Подсчитываем количество встречающихся символов в строке
    for (char iter : other) {
        ++mapka[iter];
    }
    
    // Если в строке не ровно два различных символа, возвращаем false
    if (mapka.size() != 2) {
        return false;
    }
    
    // Проверяем, является ли строка палиндромом
    for (int i =0; i < mapka.size()/2; ++i) {
        if (other[i] != other[other.size() - i - 1]) {
            return false;
        }
    }
    return true;
}
int main() {
    std::string str;
    std::cout << "enter a string:";
    std::cin >> str;
    while(str.length() < 3 || !isIce(str)) {
        std::cout << "enter a valid string (length >=3)";
        std::getline(std::cin, str);
    }
    std::cout << "True\n\n";
    return 0;
}

#include <iostream>
#include <string>
#include <unordered_map>

bool isIce(const std::string& other) {
    std::unordered_map<char, int> mapka;
    for (char iter : other) {
        ++mapka[iter];
    }
    if (mapka.size() != 2) {
        return false;
    }
    for (int i = 0; i < mapka.size()/2; ++i) {
        if (other[i] != other[other.size() - i - 1]) {
            return false;
        }
    }
    return true;
}

