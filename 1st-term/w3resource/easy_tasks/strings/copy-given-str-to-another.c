
// Write a C program to copy a given string into another and count the number of characters copied.

#include <stdio.h>

int string_letters_counter(char str[]) {
    int letters_counter = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        ++letters_counter;
    }
    return letters_counter;
}

char* string_concatenator(char temp_string[], char any_str[], int any_str_length_counter) {
    for (size_t i = 0; i < any_str_length_counter; ++i) {
        temp_string[i] = any_str[i];
    }
    return temp_string;
}

int main() {

    char str_based[] = "12345";    // TODO
    char str_copied[] = "qwerty";   // TODO

    int str_based_length = string_letters_counter(str_based);
    int str_copied_length = string_letters_counter(str_copied);
    
    char temp_string[str_based_length + str_copied_length];

    string_concatenator(temp_string, str_based, str_based_length);
    string_concatenator(temp_string, str_copied, str_copied_length);
    printf("new_string: %s\n\n", temp_string);
}
