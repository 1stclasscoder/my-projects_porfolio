#include "./../s21_matrix.h"

int s21_equal_columns_rows(matrix_t *A, matrix_t *B) {
  int flag = S21_SUCCES;
  if (A->columns != B->columns || A->rows != B->rows) {
    flag = ERROR;
  }
  return flag;
}