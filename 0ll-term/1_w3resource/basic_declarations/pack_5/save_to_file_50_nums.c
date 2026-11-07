// Write a C program that generates 50 random numbers between -0.5 and 0.5 and writes them to the file rand.dat. 
// The first line of rand.dat contains the number of random numbers, while the next 50 lines contain 50 random numbers. 

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
int main() {
    int n = 50;
    char chr; // переменная, в которую функция fgetc сможет положить прочитанный символ, 

    // переменная-указатель, которая хранит адрес в памяти, где лежит специальная структура 
    // в ней хранится вся служебная информация о файле: 
    // его текущая позиция, режим открытия, буфер и т.д

    // Объяви указатель с именем fptr, который будет указывать на структуру типа FILE
    FILE * fptr;
    
    // Open a file for writing
    // Вызови функцию открытия файла fopen.
    // Передай ей имя файла 'rand.dat' и режим 'w' 
    // Возвращенный этой функцией адрес сохрани в переменную fptr."
    fptr = fopen("rand.dat", "w");
    if (fptr == NULL) {
      printf("Error in creating output.dat\n");
      return 0;
    }

    // Заполните генератор случайных чисел
    srand(time(NULL));

    // передаем функции указатель на файл, управляемый через fptr, записываем в него число значений

    fprintf(fptr, "%d\n", n);
    
    // Generate and write random numbers to the file
    for (int i = 0; i < n; i++) {
      // показать ровно 4 знака после запятой 
      // дополнять нулями при необходимости
      // long float, то есть тип double (дробное число двойной точности)
      fprintf(fptr, "%0.4lf\n", (rand() % 2001 - 1000) / 2.e3);

      //  берет остаток от деления на 2001. Результат всегда будет в диапазоне от 0 до 2000
      // -1000 → сдвигает диапазон. Если было 0, станет -1000
      // Теперь диапазон: от -1000 до +1000.

      // делитель написан как 2.e3, чтобы компилятор воспринял деление как дробное, 
      // а не целочисленное, иначе мы бы потеряли дробную часть).
      
    }
    
    // Close the file
    fclose(fptr);
    
    // Open the file for reading
    fptr = fopen("rand.dat", "r");

    // fgetc возвращает прочитанный символ как результат своей работы
    // Считывает один следующий символ из открытого файла и сохраняет его в переменную.
    // После этого внутренний 'курсор' файла автоматически сдвинется на один символ вперед.
    chr = fgetc(fptr);
    
    // Print the contents of the file
    while (chr != EOF)
    {
      printf("%c", chr);
      // прочитай СЛЕДУЮЩИЙ символ из файла и положи его на место старого
      chr = fgetc(fptr);
    }
    
    // Close the file
    fclose(fptr);
    
    return 0;
}
