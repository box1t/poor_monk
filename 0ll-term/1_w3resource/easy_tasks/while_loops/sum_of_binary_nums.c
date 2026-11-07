// Write a program in C to sum binary numbers.

#include <stdio.h>
#include <string.h>

// Вспомогательная функция для переворота строки (так как мы записываем результат с конца)
void reverse_string(char *str) {
    int left = 0;
    int right = strlen(str) - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

// Основная функция сложения двух двоичных строк
void add_binary(const char *bin1, const char *bin2, char *result) {
    int i = strlen(bin1) - 1; // Указатель на последний символ первой строки
    int j = strlen(bin2) - 1; // Указатель на последний символ второй строки
    int k = 0;                // Указатель для записи результата
    int carry = 0;            // Перенос (carry) в старший разряд

    // Цикл продолжается, пока есть цифры в любой из строк ИЛИ есть перенос
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry; // Начинаем с переноса с предыдущего шага

        // Если в первой строке еще есть цифры, добавляем их к сумме
        if (i >= 0) {
            sum += bin1[i] - '0'; // Преобразуем символ '0' или '1' в число 0 или 1
            i--;
        }
        
        // Если во второй строке еще есть цифры, добавляем их к сумме
        if (j >= 0) {
            sum += bin2[j] - '0';
            j--;
        }
        
        // Записываем текущий бит результата (остаток от деления на 2)
        result[k] = (sum % 2) + '0'; // Преобразуем число 0 или 1 обратно в символ
        carry = sum / 2;             // Вычисляем новый перенос (0 или 1)
        k++;
    }
    
    // Завершаем строку результата нуль-терминатором
    result[k] = '\0';
    
    // Так как мы записывали биты справа налево, переворачиваем итоговую строку
    reverse_string(result);
}

int main() {
    char bin1[256], bin2[256], result[256];
    
    printf("=== Сложение двоичных чисел ===\n");
    
    printf("Введите первое двоичное число: ");
    scanf("%255s", bin1); // %255s защищает от переполнения буфера
    
    printf("Введите второе двоичное число: ");
    scanf("%255s", bin2);
    
    add_binary(bin1, bin2, result);
    
    printf("\n--- Результат ---\n");
    printf("  %s\n", bin1);
    printf("+ %s\n", bin2);
    printf("------\n");
    printf("  %s\n", result);
    
    return 0;
}