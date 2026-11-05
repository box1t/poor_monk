// Write a C program to check a password ensuring it contains at least one uppercase letter, one lowercase letter, and one digit.

#include <stdio.h>
#include <ctype.h>

int main() {
    char password[100];

    int has_upper = 0;
    int has_lower = 0;
    int has_digit = 0;

    scanf("%s", password);

    for (int i = 0; password[i] != '\0'; i++) {

        if (isupper(password[i])) {
            has_upper = 1;
        }

        if (islower(password[i])) {
            has_lower = 1;
        }

        if (isdigit(password[i])) {
            has_digit = 1;
        }
    }

    if (has_upper && has_lower && has_digit) {
        printf("Valid password");
    }
    else {
        printf("Invalid password");
    }

    return 0;
}