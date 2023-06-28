#include "s21_matrix.h"



int main() {
    int rows_A = 3;
    int columns_A = 3;
    matrix_t A;

    // int rows_B = 2;
    // int columns_B = 3;
    // matrix_t B;

    matrix_t result;

    
    s21_create_matrix(rows_A, columns_A, &A);
    scan_matrix_from_terminal(rows_A, columns_A, &A);
    show_matrix_in_terminal(rows_A, columns_A, &A);
    
    // s21_create_matrix(rows_B, columns_B, &B);
    // scan_matrix_from_terminal(rows_B, columns_B, &B);
    // show_matrix_in_terminal(rows_B, columns_B, &B);

    // // --------------- COMPARISON --------------
    // s21_eq_matrix(&A, &B);

    // // --------------- SUM --------------  
    // if (!s21_sum_matrix(&A, &B, &result))
    //     show_matrix_in_terminal(rows_A, columns_A, &result);

    // // --------------- SUB --------------
    // if (!s21_sub_matrix(&A, &B, &result))
    //     show_matrix_in_terminal(rows_A, columns_A, &result);

    // // --------------- MULT ON SCALAR --------------
    // if (!s21_mult_number(&A, 3, &result))
    //     show_matrix_in_terminal(rows_A, columns_A, &result);
    
    // // --------------- MATRIX MULT --------------
    // if (!s21_mult_matrix(&A, &B, &result))
    //     show_matrix_in_terminal(rows_A, columns_A, &result);

    // --------------- MATRIX TRANSPOSE --------------
    if (!s21_transpose(&A, &result))
        show_matrix_in_terminal(columns_A, rows_A, &result);

    // --------------- MATRIX DETERMINANT --------------
    double res;
    if (!s21_determinant(&A, &res))
        printf("Determinant: %.2f\n", res);

    // --------------- MATRIX COMPLEMENT --------------
    if (!s21_calc_complements(&A, &result))
        show_matrix_in_terminal(columns_A, rows_A, &result);

    // --------------- MATRIX INVERSE --------------
    if (!s21_inverse_matrix(&A, &result))
        show_matrix_in_terminal(columns_A, rows_A, &result);
}



// 0 - OK 
// 1 - INCORRECT_MATRIX_ERROR
// 2 - CALCULATION_ERROR

// ###################-- создание, удаление --###################

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    int res = INCORRECT_MATRIX_ERROR;
    if (rows > 0 && columns > 0) {
        result->rows = rows;
        result->columns = columns;
        result->matrix = calloc(rows, sizeof(double *));

        if (result->matrix != NULL) {
            for (int i = 0; i < rows; i++) {
                result->matrix[i] = calloc(columns, sizeof(double));
            }
            res = OK;
        }
    }
    printf("Result from matrix create: %d\n", res);
    return res;
}

void s21_remove_matrix(matrix_t *A) {
    if (A) {
        for (int i = 0; i < A -> rows; i++)
            free(A->matrix[i]);
        free(A->matrix);
    }
}


// ###################-- проверка матриц на эквивалентность --######
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int res = SUCCESS;
    if (is_matrix_correct_check(A) != OK ||
        is_matrix_correct_check(B) != OK ||
        A->columns != B->columns ||
        A->rows != B->rows)
        res = FAILURE;
    else {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > PRECISION)
                    res = FAILURE;
            }
        }
    }
    printf("Result from matrix equal check: %d\n", res);
    return res;
}


// ###################-- суммирование и вычитание матриц --###########

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = sum_sub_matrix(A, B, result, 1);
    printf("Result from sum_matrix: %d\n", res);        
    return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = sum_sub_matrix(A, B, result, 0);
    printf("Result from sub_matrix: %d\n", res);        
    return res;
}


int sum_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int operation) {
    int res = INCORRECT_MATRIX_ERROR;
    if (!is_matrix_correct_check(A) && !is_matrix_correct_check(B)) {
        if (is_matrix_equal_size(A, B)) {
        res = CALCULATION_ERROR;
        } else if (!s21_create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < A->rows; i++)
            for (int j = 0; j < A->columns; j++) {
                if (operation)
                    result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
                else
                    result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        res = OK;
        }
    }
    return res;
}

// ###################-- умножение матрицы на скаляр --###############
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    int res = INCORRECT_MATRIX_ERROR;
    if (!is_matrix_correct_check(A)) {
        if (!s21_create_matrix(A->rows, A->columns, result)) {
            for (int i = 0; i < A->rows; i++)
                for (int j = 0; j < A->columns; j++)
                    result->matrix[i][j] = A->matrix[i][j] * number;
            res = OK;
        }
    }
    printf("Result from matrix_mult_number: %d\n", res); 
    return res;
}

// ###################-- перемножение матриц --#######################

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int res = INCORRECT_MATRIX_ERROR;
    if (!is_matrix_correct_check(A) && !is_matrix_correct_check(B)) {
        if (A->columns != B->rows) {
        res = CALCULATION_ERROR;
        } else if (!s21_create_matrix(A->rows, A->columns, result)) {
        for (int i = 0; i < A->rows; i++)
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = 0;
                for (int n = 0; n < A->columns; n++)
                    result->matrix[i][j] += A->matrix[i][n] * B->matrix[n][j];
            }
        res = OK;
        }
    }
    printf("Result from matrix_mult: %d\n", res); 
    return res;
}

// ###################-- транспонирование матрицы --###################

int s21_transpose(matrix_t *A, matrix_t *result) {
    int res = INCORRECT_MATRIX_ERROR;
    if (!is_matrix_correct_check(A)) {
        if (!s21_create_matrix(A->columns, A->rows, result)) {
            for (int i = 0; i < A->columns; i++)
                for (int j = 0; j < A->rows; j++)
                    result->matrix[i][j] = A->matrix[j][i];
            res = OK;
        }
    }
    printf("Result from matrix_transpose: %d\n", res); 
    return res;
}

// ###################-- нахождение определителя матрицы --###################

int s21_determinant(matrix_t *A, double *result) {
    int res = INCORRECT_MATRIX_ERROR;
    if (!is_matrix_correct_check(A)) {
        res = OK;
        if (A->rows != A->columns) 
            res = CALCULATION_ERROR;
        else if (A->rows == 1) 
            *result = A->matrix[0][0];
        else 
            *result = recursive_determinant_calc(A);
    }
    return res;
}

double recursive_determinant_calc(matrix_t * A) {
    double res = 0;
    if (A->rows == 2) {
            res = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        for (int i = 0; i < A->rows; i++) {
            matrix_t minor_matrix;
            get_minor(1, i + 1, A, &minor_matrix);
            res += pow((-1), i) * A->matrix[0][i] * recursive_determinant_calc(&minor_matrix);
            s21_remove_matrix(&minor_matrix);
        }
    }
    return res;
}

// ########-- нахождение матрицы алгебраических дополнений --#########

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int res = INCORRECT_MATRIX_ERROR;
    if (!is_matrix_correct_check(A)) {
        res = CALCULATION_ERROR;
        if (A->rows == A->columns) {
            res = s21_create_matrix(A->columns, A->rows, result);
            if (!res)
                res = complements_calculation(A, result);
        }
    }
    return res;
}

int complements_calculation(matrix_t *A, matrix_t *result) {
    int res = OK;
    result->matrix[0][0] = 1;
    if (A->rows != 1) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                double determinant;
                matrix_t minor_matrix;
                res = get_minor(i + 1, j + 1, A, &minor_matrix);
                if (!res) {
                    res = s21_determinant(&minor_matrix, &determinant);
                    if (!res)
                        result->matrix[i][j] = pow((-1), i + j) * determinant;
                }
                s21_remove_matrix(&minor_matrix);
            }
        }
    }
    return res;
}

// ########-- нахождение обратной матрицы --#########

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int res = INCORRECT_MATRIX_ERROR;

    if (!is_matrix_correct_check(A)) {
        res = CALCULATION_ERROR;
        double determinant;
        s21_determinant(A, &determinant);
        if (fabs(determinant - 0) > PRECISION) {
            matrix_t m_calc;
            res = s21_calc_complements(A, &m_calc);
            if (!res) {
                matrix_t m_transpose;
                res = s21_transpose(&m_calc, &m_transpose);
                if (!res) {
                    int num = 1 / determinant;
                    s21_mult_number(&m_transpose, num, result);
                }
                s21_remove_matrix(&m_transpose);
            }
            s21_remove_matrix(&m_calc);
        }
    }
    return res;
}

// ###################-- вспомогательные функции --###################

void scan_matrix_from_terminal(int rows, int columns, matrix_t *M) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            double num = 0;
            printf("Введи число (cтрока %d, колонка %d)  ", i, j);
            scanf("%lf", &num);
            M->matrix[i][j] = num;
        }
    }
    printf("\n");
}

void show_matrix_in_terminal(int rows, int columns, matrix_t *M) {
    printf("MATRIX:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%.2f ", M->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int is_matrix_correct_check(matrix_t * M) {
    int res = OK;
    if (!M || !M->matrix || M->rows < 1 || M->columns < 1)
        res = INCORRECT_MATRIX_ERROR;
    printf("Result from matrix correct check: %d\n", res);
    return res;
}

int is_matrix_equal_size(matrix_t *A, matrix_t *B) {
    int res = 0;
    if (A->rows != B->rows || A->columns != B->columns) 
        res = 1;
    printf("Result from matrix matrix_equal_size: %d\n", res);  
    return res;
}

int get_minor(int row, int column, matrix_t *A, matrix_t *minor_matrix) {
    int res = INCORRECT_MATRIX_ERROR;
    if (A->matrix) {
        res = CALCULATION_ERROR;
        if (!s21_create_matrix(A->rows - 1, A->columns - 1, minor_matrix)) {
            res = OK;
            int m, n;
            for (int i = 0; i < A->rows; i++) {
                m = i;
                if (i > row - 1)
                    m--;
                for (int j = 0; j < A->columns; j++) {
                    n = j;
                    if (j > column - 1)
                        n--;
                    if (i != row - 1 && j != column - 1)
                        minor_matrix->matrix[m][n] = A->matrix[i][j];
                }
            }
        }
    }
    return res;
}


