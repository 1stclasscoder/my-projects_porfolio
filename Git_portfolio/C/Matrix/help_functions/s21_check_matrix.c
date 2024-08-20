#include "./../s21_matrix.h"

int s21_check_matrix(matrix_t *Z) {
  int flag = S21_SUCCES;
  if (Z == NULL || Z->matrix == NULL || Z->rows <= 0 || Z->columns <= 0) {
    flag = UNCORRECT_MATRIX;
  }
  return flag;
}