#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <thrust/device_ptr.h>
#include <thrust/extrema.h>

#define CSC(call)                                                              \
do {                                                                           \
    cudaError_t status = call;                                                 \
    if (status != cudaSuccess) {                                               \
        fprintf(stderr, "ERROR in %s:%d. Message: %s\n", __FILE__, __LINE__,   \
                cudaGetErrorString(status));                                   \
        exit(0);                                                               \
    }                                                                          \
} while (0)

struct absolute_comparator {
    __host__ __device__ bool operator()(double a, double b) const {
        return fabs(a) < fabs(b);
    }
};

__global__ void swap_rows_kernel(double* matrix, double* vector_b, int n, int row_a, int row_b) {
    for (int col_idx = blockIdx.x * blockDim.x + threadIdx.x; col_idx < n; col_idx += blockDim.x * gridDim.x) {
        double temp_val = matrix[col_idx * n + row_a];
        matrix[col_idx * n + row_a] = matrix[col_idx * n + row_b];
        matrix[col_idx * n + row_b] = temp_val;

        if (col_idx == 0) {
            double temp_b = vector_b[row_a];
            vector_b[row_a] = vector_b[row_b];
            vector_b[row_b] = temp_b;
        }
    }
}

__global__ void forward_elimination_kernel(double* matrix, double* vector_b, int n, int step_idx) {
    for (int target_row = blockIdx.x * blockDim.x + threadIdx.x + step_idx + 1; target_row < n; target_row += blockDim.x * gridDim.x) {
        double pivot_value = matrix[step_idx * n + step_idx];
        double multiplier = matrix[step_idx * n + target_row] / pivot_value;

        for (int current_col = blockIdx.y * blockDim.y + threadIdx.y + step_idx + 1; current_col < n; current_col += blockDim.y * gridDim.y) {
            matrix[current_col * n + target_row] -= multiplier * matrix[current_col * n + step_idx];
        }

        if (blockIdx.y * blockDim.y + threadIdx.y == 0) {
            vector_b[target_row] -= multiplier * vector_b[step_idx];
        }
    }
}

int find_pivot_row_index(double* d_matrix, int n, int step_idx) {
    thrust::device_ptr<double> column_start = thrust::device_pointer_cast(d_matrix + step_idx * n);
    auto max_it = thrust::max_element(column_start + step_idx, column_start + n, absolute_comparator());
    return static_cast<int>(max_it - column_start);
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

    for (int i = 0; i < n; i++) 
        for (int j = 0; j < n; j++) 
            scanf("%lf", &h_matrix[j * n + i]);
            
    for (int i = 0; i < n; i++) 
        scanf("%lf", &h_vector_b[i]);

    double *d_matrix, *d_vector_b;
    CSC(cudaMalloc(&d_matrix, n * n * sizeof(double)));
    CSC(cudaMalloc(&d_vector_b, n * sizeof(double)));
    CSC(cudaMemcpy(d_matrix, h_matrix, n * n * sizeof(double), cudaMemcpyHostToDevice));
    CSC(cudaMemcpy(d_vector_b, h_vector_b, n * sizeof(double), cudaMemcpyHostToDevice));


    dim3 grid_cfg(16, 16);  
    dim3 block_cfg(16, 16); 
    
    int grid_swap = 256;
    int block_swap = 256;

    for (int step = 0; step < n; step++) {
        int best_row = find_pivot_row_index(d_matrix, n, step);
        if (best_row != step) {
            swap_rows_kernel<<<grid_swap, block_swap>>>(d_matrix, d_vector_b, n, step, best_row);
        }        
        forward_elimination_kernel<<<grid_cfg, block_cfg>>>(d_matrix, d_vector_b, n, step);
    }
    
    CSC(cudaDeviceSynchronize());
    CSC(cudaMemcpy(h_matrix, d_matrix, n * n * sizeof(double), cudaMemcpyDeviceToHost));
    CSC(cudaMemcpy(h_vector_b, d_vector_b, n * sizeof(double), cudaMemcpyDeviceToHost));

    solve_back_substitution(h_matrix, h_vector_b, h_result, n);

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
    
    CSC(cudaFree(d_matrix)); 
    CSC(cudaFree(d_vector_b));
    return 0;
}