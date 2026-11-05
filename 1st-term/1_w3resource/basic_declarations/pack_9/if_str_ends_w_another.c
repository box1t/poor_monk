// Write a C program that accepts two strings and checks whether the second string is present in the last part of the first string.

#include <stdio.h>

int main() {
    char str1[100];
    char str2[100];

    // fgets читает целую строку (включая пробелы) и защищает от переполнения буфера.
    // scanf("%s") читает только одно слово (до первого пробела) и по умолчанию опасен, так как может перезаписать память за пределами массива.
    fgets(str1, sizeof(str1), stdin);
    fgets(str2, sizeof(str2), stdin);

    int i = 0;
    int j = 0;

    while (str1[i] != '\0') {
        ++i;
    }

    while (str2[j] != '\0') {
        ++j;
    }

    // Если убрать проверку i из условия while, программа попадет в ловушку, когда вторая строка длиннее первой. 
    // Если строка не входит (ни полностью, ни частично так, чтобы дойти до начала str2), цикл while прервется досрочно из-за несовпадения символов
    while (i >= 0 && j >= 0 && str1[i] == str2[j]) {
        --i;
        --j;
    }

    // Почему мы сравниваем именно j?
    if (j < 0) {
        printf("present");
    }
    else {
        printf("not present");
    }

}
