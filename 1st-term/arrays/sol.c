

#include <stdio.h>
#include <math.h>

int main() {

    int a, b;
    scanf("%d %d", &a, &b);

    if (a == 0) {
        if (b == 0) {
            printf("INF");
        } else{
            printf("NO");
        }
    } else {
        if (-b % a == 0) {
            printf("%d", - b / a);
        } 
        else {
            printf("NO");
        }
    }

    return 0;
}
