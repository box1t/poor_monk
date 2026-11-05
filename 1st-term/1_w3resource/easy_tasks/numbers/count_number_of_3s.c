
// Write a C program that reads an integer (7 digits or fewer) and counts the number of 3s in the given number. 

/*
🔹 Это итеративный алгоритм перебора разрядов числа.
Почему алгоритм именно такой:


1️⃣ Берём number.
2️⃣ Запускаем while (number > 0).
3️⃣ На каждой итерации:

    Берём digit = number % 10.
    Проверяем, if (digit == 3), увеличиваем counter.
    Убираем цифру number /= 10.
    4️⃣ Когда number == 0, цикл завершается.
    5️⃣ Выводим counter.

*/

#include <stdio.h>

int main() {
    int number = 123453;
    int start_number = number;
    int counter = 0;
    int digit = 0;
    while (number > 0) {
        digit = number % 10;
        if (digit == 3) {
            ++counter;
        }
        number /= 10;
    }
    printf("Число троек в числе (%d): (%d)\n\n", start_number, counter);
    
}

