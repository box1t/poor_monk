
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void qrDecomposition(double** A, double** Q, double** R, int m, int n) {
    for (int k = 0; k < n; k++) {
        double norm = 0.0;
        for (int i = 0; i < m; i++) {
            norm += A[i][k] * A[i][k];
        }
        R[k][k] = sqrt(norm);
        
        for (int i = 0; i < m; i++) {
            Q[i][k] = A[i][k] / R[k][k];
        }
        
        for (int j = k + 1; j < n; j++) {
            R[k][j] = 0.0;
            for (int i = 0; i < m; i++) {
                R[k][j] += Q[i][k] * A[i][j];
            }
            for (int i = 0; i < m; i++) {
                A[i][j] -= Q[i][k] * R[k][j];
            }
        }
    }
}

int main() {
    int m = 3, n = 3;
    double** A = (double**)malloc(m * sizeof(double*));
    double** Q = (double**)malloc(m * sizeof(double*));
    double** R = (double**)malloc(n * sizeof(double*));
    
    for (int i = 0; i < m; i++) {
        A[i] = (double*)malloc(n * sizeof(double));
        Q[i] = (double*)malloc(n * sizeof(double));
    }
    for (int i = 0; i < n; i++) {
        R[i] = (double*)malloc(n * sizeof(double));
    }
    
    // Example matrix
    A[0][0] = 12; A[0][1] = -51; A[0][2] = 4;
    A[1][0] = 6;  A[1][1] = 167; A[1][2] = -68;
    A[2][0] = -4; A[2][1] = 24;  A[2][2] = -41;
    
    qrDecomposition(A, Q, R, m, n);
    
    printf("Matrix Q:\n");
    printMatrix(Q, m, n);
    
    printf("Matrix R:\n");
    printMatrix(R, n, n);
    
    for (int i = 0; i < m; i++) {
        free(A[i]);
        free(Q[i]);
    }
    for (int i = 0; i < n; i++) {
        free(R[i]);
    }
    free(A);
    free(Q);
    free(R);
    
    return 0;
}
