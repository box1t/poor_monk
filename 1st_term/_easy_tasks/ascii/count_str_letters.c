
// Выполните подсчёт количества букв в строке в Си при помощи ASCII

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

int count_letters_in_string(char str[]) {
    int counter = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (isalpha(str[i])) {
            ++counter;
        }
    }
    return counter;
}

int main() {
    setlocale(LC_CTYPE, "");  // ✅ Подключаем поддержку кириллицы
    int str_len = 100;
    char str[str_len];
    
    printf("Введите строку: ");
    fgets(str, str_len, stdin);

    // ✅ Удаление символа `\n`, если он есть
    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    
    int letters_counter = count_letters_in_string(str);
    printf("Letters in string [%s] : [%d]\n\n", str, letters_counter);
}

