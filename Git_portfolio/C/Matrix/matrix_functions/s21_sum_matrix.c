#include "./../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = S21_SUCCES;
  if (s21_check_matrix(A) || s21_check_matrix(B)) {
    flag = UNCORRECT_MATRIX;
  } else if (s21_equal_columns_rows(A, B)) {
    flag = ERROR;
  } else {
    flag = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*A).columns; ++j) {
        result->matrix[i][j] = (*A).matrix[i][j] + (*B).matrix[i][j];
      }
    }
  }
  return flag;
}