
#include <stdio.h>
#include <stdlib.h>

// Function to create a tridiagonal matrix
double** createTridiagonalMatrix(int n) {
    double** matrix = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)calloc(n, sizeof(double));
    }
    return matrix;
}

// Function to set values in the tridiagonal matrix
void setTridiagonalMatrix(double** matrix, int n, double* lower, double* main, double* upper) {
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            matrix[i][i-1] = lower[i-1];
        }
        matrix[i][i] = main[i];
        if (i < n-1) {
            matrix[i][i+1] = upper[i];
        }
    }
}

// Function to print the matrix
void printMatrix(double** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%6.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 4; // Size of the matrix
    double lower[] = {1.0, 2.0, 3.0}; // Lower diagonal
    double main[] = {4.0, 5.0, 6.0, 7.0}; // Main diagonal
    double upper[] = {8.0, 9.0, 10.0}; // Upper diagonal

    double** matrix = createTridiagonalMatrix(n);
    setTridiagonalMatrix(matrix, n, lower, main, upper);

    printf("Tridiagonal Matrix:\n");
    printMatrix(matrix, n);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
