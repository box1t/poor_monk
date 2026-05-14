#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>

bool absolute_compare(double a, double b) {
    return fabs(a) < fabs(b);
}

void swap_rows_cpu(double* matrix, double* vector_b, int n, int row_a, int row_b) {
    for (int col_idx = 0; col_idx < n; col_idx++) {
        double temp_val = matrix[col_idx * n + row_a];
        matrix[col_idx * n + row_a] = matrix[col_idx * n + row_b];
        matrix[col_idx * n + row_b] = temp_val;
    }
    double temp_b = vector_b[row_a];
    vector_b[row_a] = vector_b[row_b];
    vector_b[row_b] = temp_b;
}

void forward_elimination_cpu(double* matrix, double* vector_b, int n, int step_idx) {
    for (int target_row = step_idx + 1; target_row < n; target_row++) {
        double pivot_value = matrix[step_idx * n + step_idx];
        double multiplier = matrix[step_idx * n + target_row] / pivot_value;

        for (int current_col = step_idx + 1; current_col < n; current_col++) {
            matrix[current_col * n + target_row] -= multiplier * matrix[current_col * n + step_idx];
        }
        vector_b[target_row] -= multiplier * vector_b[step_idx];
    }
}

int find_pivot_row_index(double* matrix, int n, int step_idx) {
    int best_row = step_idx;
    for (int i = step_idx + 1; i < n; i++) {
        if (absolute_compare(matrix[step_idx * n + best_row], matrix[step_idx * n + i])) {
            best_row = i;
        }
    }
    return best_row;
}

void solve_back_substitution(double* matrix, double* vector_b, double* result, int n) {
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += matrix[j * n + i] * result[j];
        }
        result[i] = (vector_b[i] - sum) / matrix[i * n + i];
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    double* h_matrix = (double*)malloc(n * n * sizeof(double));
    double* h_vector_b = (double*)malloc(n * sizeof(double));
    double* h_result = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &h_matrix[j * n + i]);
        }
    }
    for (int i = 0; i < n; i++) {
        scanf("%lf", &h_vector_b[i]);
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int step = 0; step < n; step++) {
        int best_row = find_pivot_row_index(h_matrix, n, step);
        if (best_row != step) {
            swap_rows_cpu(h_matrix, h_vector_b, n, step, best_row);
        }        
        forward_elimination_cpu(h_matrix, h_vector_b, n, step);
    }
    
    solve_back_substitution(h_matrix, h_vector_b, h_result, n);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    fprintf(stderr, "CPU Total Time: %.4f ms\n", elapsed.count());

    for (int i = 0; i < n; ++i) {
        printf("%.10e", h_result[i]);
        if (i < n - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

    free(h_matrix);
    free(h_vector_b);
    free(h_result);

    return 0;
}