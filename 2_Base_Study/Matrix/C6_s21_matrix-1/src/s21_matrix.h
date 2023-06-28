#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUCCESS 1
#define FAILURE 0
#define PRECISION 1e-7

enum {
    OK = 0,
    INCORRECT_MATRIX_ERROR = 1,
    CALCULATION_ERROR = 2,
};

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);


int is_matrix_correct_check(matrix_t *matrix);
int sum_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int operation);
int is_matrix_equal_size(matrix_t *A, matrix_t *B);
int complements_calculation(matrix_t *A, matrix_t *result);
double recursive_determinant_calc(matrix_t *A);
int get_minor(int row, int column, matrix_t *A, matrix_t *minor_matrix);
void show_matrix_in_terminal(int rows, int columns, matrix_t *M);
void scan_matrix_from_terminal(int rows, int columns, matrix_t *M);

#endif  // SRC_S21_MATRIX_H_