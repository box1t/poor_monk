// Напишите программу на языке C, которая принимает от пользователя сумму в рублях и выдает минимальное количество купюр и монет для её выдачи
// Купюры: 1000, 500, 200, 100, 50, 10
// Монеты: 5, 2, 1


#include <stdio.h>

int main() {
    int values[] = {1000, 500, 200, 100, 50, 10, 5, 2, 1};
    
    int count_values = sizeof(values) / sizeof(values[0]);

    int n;
    printf("Введите сумму: ");
    scanf("%d", &n);

    printf("Value\tAmount\n");
    printf("----------------\n");

    for (int i = 0; i < count_values; ++i) {
        int amount = n / values[i]; 
        
        if (amount > 0) {
            printf("%d\t%d\n", values[i], amount);
            n = n % values[i]; 
        }
    }

    return 0;
}