
#include <stdio.h>
#include <math.h>

int main() {
    float a, b, c;
    scanf("%f%f%f", &a, &b, &c);

    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                printf("any");
            }
            else {
                printf("incorrect");
            }
        }
        else {
                printf("incorrect");
        }
    }
    else {
        float discriminant = (b * b) - 4 * a * c;
        if (discriminant > 0) {
            float result_1 = ((- b) + sqrt(discriminant) ) / (2*a); 
            float result_2 = ((- b) - sqrt(discriminant) ) / (2*a);
            printf("%.6f %.6f", result_1, result_2);
        }
        else if (discriminant == 0) {
            printf("%.6f", (-b) / (2*a));
        }
        else {
            printf("imaginary");
        }
    }
}
