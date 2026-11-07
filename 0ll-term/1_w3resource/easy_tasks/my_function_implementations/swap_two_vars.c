
// Swap two numbers without a temporary variable

/*
1. Как выполнить эту задачу при помощи
    - арифметических операций
    - битовых операций


над чем арифметика?


какие битовые операции это поддерживают?
при каком условии это доступно? если значения лежат в памяти последовательно?
а если это две переменные, это уже не гарантируется?

как битовый xor решит эту задачу?



x = x ^ y; stores the result of x XOR y in x.
y = x ^ y; stores the original value of x in y by performing x XOR y (since x now holds x XOR y, this operation effectively isolates the original x).
x = x ^ y; stores the original value of y in x by performing x XOR y (since y now holds the original x).


*/

#include <stdio.h>

int main() {
    int number_one, number_two;
    scanf("%d%d", &number_one, &number_two);
    printf("%d::%d\n", number_one, number_two);
    
    number_one = number_one + number_two;
    number_two = number_one - number_two;
    number_one = number_one - number_two;

    printf("%d::%d\n", number_one, number_two);
}

/*
#include <stdio.h>

int main() {
    int number_one, number_two;
    scanf("%d%d", &number_one, &number_two);
    printf("%d::%d\n", number_one, number_two);

    number_one = number_one ^ number_two;
    number_two = number_one ^ number_two;
    number_one = number_one ^ number_two;

    printf("%d::%d\n", number_one, number_two);

}
*/