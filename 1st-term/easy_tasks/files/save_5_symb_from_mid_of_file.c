
// Как сохранить 5 символов из середины файла в массив?

/*
1. 
- Открыть файл
- Сдвинуться в конец, чтобы узнать его размер.
- Завести переменную, присвоив значение половины размера в байтах
- Произвести чтение с момента середины, в размере 5 символов, в поток вывода "массив"

*/


#include <stdio.h>

int main() {
    FILE *file = fopen("my_file.txt", "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);

    long middle = file_size / 2;

    fseek(file, middle, SEEK_SET);

    char arr[6] = {0};
    fread(arr, sizeof(char), 5, file);

    printf("5 символов из середины: %s\n", arr);

    fclose(file);
    return 0;
}

