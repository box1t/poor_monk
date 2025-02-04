
// Sum the series 1^4+2^4+4^4+...+m^4

/*
верно ли, что int легко кастуется к size_t?
проще чем к double / float?


*/

#include <stdio.h>
#include <math.h>

int main() {
    int degree = 4;
    size_t sum;
    int m;
    scanf("%d", &m);
    
    for (size_t i = 1; i <= m; ++i) {
        sum += pow(i, degree);
    }
    printf("%ld", sum);
}

/*
их решение сильно отличается от твоего. я или они ошиблись?

#include <stdio.h>
int main() {
    int i, j, n, sum_int = 0;

    // Prompt user for input
    printf("Input a positive number less than 100: \n");

    // Read the input value
    scanf("%d", &n);

    // Check if the input is valid
    if (n < 1 || n >= 100) {
        printf("Wrong input\n");
        return 0;
    }

    j = 1;
    for (i = 1; j <= n; i++) {
        sum_int += j * j * j * j;
        j += i;
    }

    // Display the result
    printf("Sum of the series is %d\n", sum_int);

    return 0;
}

*/