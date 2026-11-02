// Write a program that simulates a dice using the rand() function.
// Experts: Simulate “real” randomness that cannot be recreated.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    unsigned int seed = 0;
    
    // 1. Текущее время в секундах (базовая энтропия)
    seed ^= (unsigned int)time(NULL);
    
    // 2. Процессорное время, затраченное программой с момента запуска.
    // Оно микроскопически отличается при каждом запуске.
    seed ^= (unsigned int)clock();
    
    // 3. Адрес переменной seed в памяти. 
    // Благодаря ASLR (рандомизации адресного пространства) в современных ОС 
    // этот адрес будет разным при каждом запуске программы.
    seed ^= (unsigned int)&seed;

    // Инициализируем генератор нашим уникальным seed
    srand(seed);

    // Генерация броска кубика (от 1 до 6)
    int dice_roll = (rand() % 6) + 1;

    printf("🎲 Выпало число: %d\n", dice_roll);

    return 0;
}