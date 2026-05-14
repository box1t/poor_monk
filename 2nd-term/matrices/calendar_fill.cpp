/*
Это почти задача на обработку матрицы.
Что если поменять направление обхода?
Справа налево? По столбцам?
*/

#include <iostream>
#include <vector>
#include <string>

// Заполнение календаря
std::vector<std::string> fill_calendar(int first_week_day, int days_in_month) {
    std::vector<std::string> calendar_vec; // Вектор для хранения строк календаря
    std::string buffer_string; // Буферная строка
    int day_counter = 1; // Счетчик дней для заполнения текущей строки

    // Добавляем пробелы в первую строку до начала первого дня
    for (int i = 1; i < first_week_day; ++i) { // day_counter не связан с пробелами
        buffer_string += "   ";
    }

    // Заполнение текущей строки днями с учетом пробелов
    while (day_counter <= days_in_month) {
        if (day_counter < 10) {
            buffer_string += " " + std::to_string(day_counter) + " "; // Однозначные числа
        } else {
            buffer_string += std::to_string(day_counter) + " "; // Двузначные числа
        }

        // Перенос заполненной (7 днями) строки в вектор
        if ((first_week_day + day_counter - 1) % 7 == 0) { 
            calendar_vec.push_back(buffer_string);
            buffer_string.clear(); // Очищаем строку для новой недели
        }

        ++day_counter;
    }

    // Добавляем оставшуюся строку, если она не пустая
    if (!buffer_string.empty()) {
        calendar_vec.push_back(buffer_string);
    }
    return calendar_vec;
}

void print_calendar(const std::vector<std::string>& calendar_vec) {
    for (const std::string& line : calendar_vec) {
        // Печатаем строку без лишних пробелов в конце
        std::cout << line.substr(0, line.size() - 1) << std::endl;
    }
}

int main() {
    int first_week_day, days_in_month;
    std::cin >> first_week_day >> days_in_month;

    std::vector<std::string> calendar = fill_calendar(first_week_day, days_in_month);
    print_calendar(calendar);
    return 0;
}

