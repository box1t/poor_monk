
/*
Matrix_lib.

*/

#include <stdio.h>
#define ARR_SIZE 3


void init_matrix(int arr_first[][ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            scanf("%d", &arr_first[i][j]);
        }
    }
}

/*

Как ввести с клавиатуры произвольное имя? 
Могу ли подставить на первое место строку файла иниц? 
могу ли выбрать режим ввода программы? 
сделать, как ирбит лаба switch case? 6 лаб для ЧМ? и на них обкатать тестирование.

*/

/*
Ошибка в задаче про диагонали: ты считал, что i == j.
но надо считать i i элементы.
почему?
в чем я мыслил неверно?

*/

// Достаточно ли этого?
void init_matrix_from_file(int arr_first[][ARR_SIZE], char file_name[]) {
    FILE* file_desc = fopen(file_name, "r"); 
    fread(file_desc, ARR_SIZE, sizeof(int), arr_first);
    fclose(file_desc);
}



void print_matrix(int arr_first[][ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            printf("%d ", arr_first[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

int transpose_matrix(int arr_first[][ARR_SIZE]) {
    int arr_transposed[ARR_SIZE][ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            arr_first[j][i] = arr_transposed[i][j];
        }
    }
    return arr_transposed;
}

// я не знаю, как это провернуть даже с точки зрения математики. слышал что-то про разбиение на четные степени.
int matrix_pow(int arr_first[][ARR_SIZE], int power) {
    
}

int count_matrix_trace(int arr_first[][ARR_SIZE]) {
    int trace = 0;
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            if (i == j) {
                trace += arr_first[i][j];
            }
        }
    }
    return trace;
}

int count_matrix_back_trace(int arr_first[][ARR_SIZE]) {
    int back_trace = 0;
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            if (j == i) {
                back_trace += arr_first[j][i];
            }
        }
    }
    return back_trace;
}

int swap_matrix_traces(int arr_first[][ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            if (i == j) {

            }
        }
    }
    return arr_first;
}

int sum_matrices(int arr_first[][ARR_SIZE], int arr_second[][ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            arr_first[i][j] += arr_second[i][j];
        }
    }
    return arr_first;
}

int substract_matrices(int arr_first[][ARR_SIZE], int arr_second[][ARR_SIZE]) {
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            arr_first[i][j] -= arr_second[i][j];
        }
    }
    return arr_first;
}


// int **mmultiply(int **a, int **b, int size);

int product_quad_matrices(int arr_first[][ARR_SIZE], int arr_second[][ARR_SIZE]) {
    int result_matr[ARR_SIZE][ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            result_matr[i][j] = arr_first[i][j] * arr_second[j][i];
        }
    }
    return result_matr;
}

int product_matrix_on_transpose_matrix(int arr_first[][ARR_SIZE]) {
    int transposed_matrix = transpose_matrix(arr_first);
    int result_matrix[ARR_SIZE][ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; ++i) {
        for (int j = 0; j < ARR_SIZE; ++j) {
            result_matrix = arr_first[i][j] * transposed_matrix[j][i];
        }
    }
}


// kormen task
int product_rectangle_matrices(int arr_first[][ARR_SIZE]) {

}

int product_of_matr_sequence() {

}


int main() {
    int arr_first[ARR_SIZE][ARR_SIZE];
    int arr_second[ARR_SIZE][ARR_SIZE];
    int arr_result[ARR_SIZE][ARR_SIZE];
    char file_name[10];
    scanf("%s", &file_name);
    init_matrix(arr_first);
    print_matrix(arr_first);

    // init_matrix();
    // arr_result = sum_matrices(arr_first[ARR_SIZE][ARR_SIZE], arr_second[ARR_SIZE][ARR_SIZE]);
    // print_matrix(arr_result[ARR_SIZE][ARR_SIZE]);

}