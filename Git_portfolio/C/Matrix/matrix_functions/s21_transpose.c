#include "./../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = S21_SUCCES;
  if (s21_check_matrix(A)) {
    flag = UNCORRECT_MATRIX;
  } else {
    flag = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*A).columns; ++j) {
        result->matrix[j][i] = (*A).matrix[i][j];
      }
    }
  }
  return flag;
}