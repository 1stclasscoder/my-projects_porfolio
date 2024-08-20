#include "./../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = S21_SUCCES;
  if (s21_check_matrix(A)) {
    flag = UNCORRECT_MATRIX;
  } else if (A->rows != B->columns) {
    flag = ERROR;
  } else {
    flag = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*B).columns; ++j) {
        for (int l = 0; l < (*A).columns; ++l) {
          result->matrix[i][j] += (*A).matrix[i][l] * (*B).matrix[l][j];
        }
      }
    }
  }
  return flag;
}