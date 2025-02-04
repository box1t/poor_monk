
// Generate 50 random numbers in [-0.5, 0.5] and save them to a file



#include <stdio.h>
#include <stdlib.h> // rand() здесь!
#include <time.h>   // для srand()

int main() {
    FILE *file_desc = fopen("myfile.txt", "w"); // Открываем файл на запись
    if (!file_desc) { 
        perror("Ошибка открытия файла");
        return 1; 
    }

    srand(time(NULL)); // Инициализируем rand()

    for (int i = 0; i < 50; ++i) {
        double value = (rand() / (double)RAND_MAX) - 0.5; // Генерируем число в [-0.5, 0.5]
        fprintf(file_desc, "%.2f ", value); // Записываем с разделителем (пробел)
    }

    fclose(file_desc); // Закрываем файл
    return 0;
}



// а теперь оформи чтение из файла.

