// Write a C program to sum all numerical values (positive integers) embedded in a sentence.

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char sentence[100] = "12345";
    /*
    1. Как суммировать отдельно стоящие цифры?
    2. Как обрабатывать случаи, когда стоят 2 подряд и более цифр? объединять их в одно число или работать с цифрами?
    3. Как проверять символ строки на кастуемость к int?
    
    */
    
    // q1
    int res = 0;
    int current_number = 0;
    for (int i = 0; sentence[i] != '\0'; ++i) {
        if (isdigit((unsigned char)sentence[i])) { // q3
            int digit = sentence[i] - '0';
            current_number = current_number * 10 + digit; // q2
        }
        else {
            res += current_number;
            current_number = 0;
        }
    }
    res += current_number;
    
    printf("res = %d", res);
}