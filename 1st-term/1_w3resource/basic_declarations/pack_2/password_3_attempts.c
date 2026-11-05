// Write a C program to validate a password with a maximum of three attempts before locking the user out.

#include <stdio.h>
#include <string.h>

int main() {
    char password[20];
    char correct_password[] = "12345";

    int attempts = 0;
    int success = 0;

    while (attempts < 3) {
        printf("Enter password: ");
        scanf("%s", password);

        if (strcmp(password, correct_password) == 0) {
            success = 1;
            break;
        }
        else {
            attempts++;
            printf("Wrong password. Attempts left: %d\n", 3 - attempts);
        }
    }

    if (success) {
        printf("Access granted");
    }
    else {
        printf("User locked out");
    }

    return 0;
}