// Return true if a digit appears in both numbers, such as the 3 in 13 and 33. 

#include <stdio.h>

int check_common_digit(int n1, int n2) {
    // Извлекаем все 4 цифры
    int n1_tens = n1 / 10;    // Десятки первого числа
    int n1_units = n1 % 10;   // Единицы первого числа
    int n2_tens = n2 / 10;    // Десятки второго числа
    int n2_units = n2 % 10;   // Единицы второго числа

    // Проверяем все 4 варианта совпадения
    if (n1_tens == n2_tens ||       // Десятки совпадают (напр., 13 и 16)
        n1_tens == n2_units ||      // Десятки первого равны единицам второго (напр., 13 и 61)
        n1_units == n2_tens ||      // Единицы первого равны десяткам второго (напр., 31 и 16)
        n1_units == n2_units) {     // Единицы совпадают (напр., 13 и 53)
        return 1;
    }
    
    return 0;
}

int main() {
    // Тесты
    printf("%d\n", check_common_digit(13, 33)); // 1 (true) - совпадают десятки (3)
    printf("%d\n", check_common_digit(16, 61)); // 1 (true) - совпадают накрест
    printf("%d\n", check_common_digit(12, 34)); // 0 (false) - общих цифр нет
    printf("%d\n", check_common_digit(99, 19)); // 1 (true) - совпадают единицы (9)

    return 0;
}