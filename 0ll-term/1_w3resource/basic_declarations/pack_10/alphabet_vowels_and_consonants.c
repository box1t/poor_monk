// Write a C program to display ASCII values for vowels and consonants separately in a formatted table.

#include <stdio.h>
#include <ctype.h>

// Helper function to check if a character is a vowel
int isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

// Helper function to print a formatted table for a given category
void printTable(const char *title, const char *letters, int count) {
    printf("\n+---------------------------------+\n");
    printf("|        %-11s        |\n", title);
    printf("+---------------------------------+\n");
    printf("| Char | Decimal |   Hex   |  Oct  |\n");
    printf("+------+---------+---------+-------+\n");
    
    for (int i = 0; i < count; i++) {
        char c = letters[i];
        printf("|  %c   |   %3d   |  0x%02X   | %03o   |\n", 
               c, c, c, c);
    }
    printf("+------+---------+---------+-------+\n");
}

int main() {
    char vowels[10];
    char consonants[42];
    int vCount = 0, cCount = 0;

    // Separate letters into vowels and consonants (both cases)
    for (char c = 'A'; c <= 'Z'; c++) {
        if (isVowel(c)) {
            vowels[vCount++] = c;
        } else {
            consonants[cCount++] = c;
        }
    }
    for (char c = 'a'; c <= 'z'; c++) {
        if (isVowel(c)) {
            vowels[vCount++] = c;
        } else {
            consonants[cCount++] = c;
        }
    }

    // Display the two tables
    printTable("VOWELS", vowels, vCount);
    printTable("CONSONANTS", consonants, cCount);

    return 0;
}