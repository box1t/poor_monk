
// Write a C program that reads a five-digit integer and determines whether or not it's a palindrome. 

#include <stdio.h>

int main() {

    int entry_number = 12326;
    int final_number = 0;
    int temp = entry_number;
    
    while (temp > 0) {
        int last_digit = temp % 10;           // Берём последнюю цифру
        final_number = final_number * 10 + last_digit;  // Добавляем в реверсированное число
        temp = temp / 10;                      // Отбрасываем последнюю цифру
    }

    if (final_number == entry_number) {
        printf("numbers (%d) and (%d) ARE palindromes\n\n", entry_number, final_number);
    } else {
        printf("numbers (%d) and (%d) ARE NOT palindromes\n\n", entry_number, final_number);
    }
}