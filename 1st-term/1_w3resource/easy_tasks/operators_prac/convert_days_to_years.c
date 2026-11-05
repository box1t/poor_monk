
// Convert days to years, months, days

// Write a C program to convert a given integer (in days) to years, 
// months and days, assuming that all months have 30 days and all years have 365 days.

#include <stdio.h>

int main() {
    int days;
    scanf("%d", &days);

    int years = days / 365;
    int months = days % 365 / 30;
    days = days % 365 % 30;
    printf("-%d---%d----%d-", years, months, days);
}