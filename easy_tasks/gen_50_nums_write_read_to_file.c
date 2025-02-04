
/* 

Write a C program that generates 50 random numbers between -0.5 and 0.5 and
writes them to the file rand.dat. 

The first line of ran.dat contains the number of random numbers, 
while the next 50 lines contain 50 random numbers.

*/



#include <stdio.h>

// этот код не дописан. здесь есть ошибки. вернись к этой задаче еще раз
// но это твой код. поздравляю, ты уже можешь писать сам, с ошибками, и ускоряться, подглядывая в ответ.
// и ты научился исправлять ошибки.

int main() {
    FILE* file_desc = fopen("rand.dat", "w");
    srand(time(NULL));
    fprintf(file_desc, "%d", 50);
    
    for (size_t i = 0; i < 50; ++i) {
        fprintf(file_desc, "%d", (rand() - 0.5)  );
    }

    fclose(file_desc);

    file_desc = fopen("rand.dat", "r");
    char str = fgetc(file_desc);
    while (str != EOF) {
        printf("%c", str);
        str = fgetc(file_desc); // что если так не сделать
    }
    fclose(file_desc);
}

