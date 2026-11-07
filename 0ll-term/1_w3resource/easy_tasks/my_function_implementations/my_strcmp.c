int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

/*

if (strcmp(a, b))        // TRUE, когда строки РАЗНЫЕ!
if (strcmp(a, b) == 0)   // TRUE, когда строки РАВНЫ — так читаемее

*/