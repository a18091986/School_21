#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *res) {
  int result_cod = 0;
  res->columns = columns;
  res->rows = rows;
  if (rows <= 0 || columns <= 0) {
    result_cod = 1;
  } else {
    res->matrix = (double **)calloc(rows, sizeof(double *));
    if (res->matrix == NULL) {
      result_cod = 1;
    } else {
      for (int i = 0; i < rows; i++) {
        res->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (!res->matrix[i]) {
          for (int j = 0; j < i; j++) {
            free(res->matrix[j]);
          }
          free(res->matrix);
          break;
        }
      }
    }
  }
  return result_cod;
}