
/*
Write a C program that generates a random number 
between 1 and 20 and asks the user to guess it. 
Use a while loop to give the user multiple chances until they guess the correct number. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int generated_var = 1 + rand() % 20;
    int input_var;

    while(1) {
        printf("Lets try! Guess a number in range (1, 20).\n");
        
        // Удалось ли считать число?
        if (scanf("%d", &input_var) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // чистим буфер ввода  
            continue;
        }
        if (input_var < 1 || input_var > 20) {
            printf("Your chosen number is (%d).\nChoose another one from correct range.", input_var);
            continue;
        }
        if (input_var != generated_var) {
            printf("Your chosen number is (%d).\nTry another one.", input_var);
            continue;
        } else {
            printf("You are right. The game is finished.");
            break;
        }
    }
}