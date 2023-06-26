#include <stdio.h>
#include <stdlib.h>
#include "s21_matrix.h"


// Все операции кроме сравнения матриц должны возвращать результирующий код:
// - 0 - OK
// - 1 - ошибка, некорректная матрица
// - 2 - ошибка вычисления (несовпадающие размеры матриц, матрица, для которой нельзя провести вычисления и т.д.)


int main(void) {

    matrix_t test_matr = {0};
    int create_matrix_result = s21_create_matrix(3, 3, &test_matr);

    printf("create matrix result: %d\n", create_matrix_result);
    
    return 0;
}