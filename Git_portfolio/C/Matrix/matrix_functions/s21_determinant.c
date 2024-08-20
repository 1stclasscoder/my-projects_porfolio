#include "./../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int flag = S21_SUCCES;
  *result = 0.0;
  if (s21_check_matrix(A)) {
    flag = UNCORRECT_MATRIX;
  } else if (A->rows != A->columns) {
    flag = ERROR;
  } else {
    *result = s21_count_determinant(A);
  }
  return flag;
}