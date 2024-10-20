/*
Это почти задача на обработку матрицы.
Что если поменять направление обхода?
Справа налево? По столбцам?
*/

#include <iostream>
#include <vector>
#include <string>

// Заполнение вектора строк с календарём
std::vector<std::string> fill_calendar(int first_week_day, int days_in_month) {
    std::vector<std::string> calendar_vec; // Вектор для хранения строк календаря
    std::string current_line; // Текущая заполняемая строка
    int day_counter = 1;

    // Добавляем пустые места в первую строку до начала первого дня
    for (int i = 1; i < first_week_day; ++i) {
        current_line += "   "; // Заполняем пробелами
    }

    // Заполнение календаря днями
    while (day_counter <= days_in_month) {
        if (day_counter < 10) {
            current_line += " " + std::to_string(day_counter) + " "; // Добавляем пробел перед однозначным числом
        } else {
            current_line += std::to_string(day_counter) + " "; // Для двузначных чисел пробел не нужен перед числом
        }

        // Если достигли конца недели (7 дней), добавляем строку в вектор и создаём новую
        if ((first_week_day + day_counter - 1) % 7 == 0) { 
            calendar_vec.push_back(current_line);
            current_line.clear(); // Очищаем строку для новой недели
        }

        ++day_counter;
    }

    // Добавляем оставшуюся строку, если она не пустая
    if (!current_line.empty()) {
        calendar_vec.push_back(current_line);
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

