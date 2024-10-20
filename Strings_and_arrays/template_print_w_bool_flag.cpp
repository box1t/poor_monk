#include <iostream>
#include <string>
#include <vector>

template <typename T>
void Print(const T& data, const std::string& lim) {
    for (const auto& iter : data) {
        std::cout << iter << lim << " ";
    }
    std::cout << "\n";
}


template <typename T>
void Print(const T& data, const std::string& lim) {
    bool first = true;  // Флаг для проверки первого элемента
    for (const auto& iter : data) {
        if (!first) {
            std::cout << lim;  // Печатаем разделитель перед элементом, если это не первый элемент
        }
        std::cout << iter;  // Печатаем сам элемент
        first = false;  // После первого элемента флаг сбрасывается
    }
    std::cout << "\n";
}


template <typename T>
void Print(const T& data, const std::string& lim) {
    for (const auto& iter : data) {
        std::cout << iter << limt << " ";
    }
    std::cout << "\n";
}


/*
Что мне надо знать про булевские флаги? 
Какие еще неплохие задачи на закрепление этого аспекта?

*/


