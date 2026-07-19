// Write a C program to sum all numerical values (positive integers) embedded in a sentence.

#include <stdio.h>
#include <ctype.h>

int main() {

    char str[200];

    printf("Enter a sentence: ");
    fgets(str, sizeof(str), stdin);

    int sum = 0;
    int number = 0;
    int inNumber = 0;

    int i = 0;

    while (str[i] != '\0') {

        // Если символ является цифрой
        if (isdigit(str[i])) {

            number = number * 10 + (str[i] - '0');
            inNumber = 1;
        }
        // Если число закончилось
        else {
            if (inNumber) {
                sum += number;

                number = 0;
                inNumber = 0;
            }
        }
        i++;
    }
    // Обработка числа, если строка заканчивается цифрой
    if (inNumber) {
        sum += number;
    }
    printf("Sum = %d\n", sum);
    return 0;
}
