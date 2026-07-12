// Write a C program that generates 50 random numbers between -0.5 and 0.5 and writes them to the file rand.dat. 
// The first line of ran.dat contains the number of random numbers, while the next 50 lines contain 50 random numbers. 

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
int main() {
  int n = 50;
  char str;
  FILE * fptr;
  
  // Open a file for writing
  fptr = fopen("rand.dat", "w");
  if (fptr == NULL) {
    printf("Error in creating output.dat\n");
    return 0;
  }

  // Seed the random number generator
  srand(time(NULL));
  
  // Write the number of values to the file
  fprintf(fptr, "%d\n", n);
  
  // Generate and write random numbers to the file
  for (int i = 0; i < n; i++) {
    fprintf(fptr, "%0.4lf\n", (rand() % 2001 - 1000) / 2.e3);
  }
  
  // Close the file
  fclose(fptr);
  
  // Open the file for reading
  fptr = fopen ("rand.dat", "r");
  str = fgetc(fptr);
  
  // Print the contents of the file
  while (str != EOF)
  {
    printf ("%c", str);
    str = fgetc(fptr);
  }
  
  // Close the file
  fclose(fptr);
  
  return 0;
}
