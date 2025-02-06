
// Выполните преобразование регистра вручную (без tolower()) в Си

// Выполните преобразование регистра вручную (без tolower()) в Си

/*

*/

#include <stdio.h>

char* str_to_low(char str[]) {
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] > 'a' && str[i] <= 'A') {
            str[i] -= ('A' - 'a');
        }
    }
    return str;
}

int main() {
    int str_len = 10;
    char str[str_len];
    printf("Input your str: ");
    fgets(str, str_len, stdin);


    if (str[0] != '\0' && str[str_len - 1] == '\n') {
        str[str_len] = '\0';
    }


    char* transformed_str = str_to_low(str);
    printf("New str: [%s]\n\n", transformed_str);
}
