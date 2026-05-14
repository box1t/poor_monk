
// Как вывести содержимое файла на экран?

#include <stdio.h>

int main() {
    
    FILE* file_desc = fopen("my_file.txt", "r");
    if (file_desc == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    int str = fgetc(file_desc);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(file_desc); 
    }
    fclose(file_desc);

    /*
    
    char c;
    while (c = getchar() != EOF) {
        

        c = getchar();// переключиться на следующий. почему это не произойдет автоматом? и что такое следующий? здесь же нет индексов!
    }
    fclose(file_desc);
    
    */
}