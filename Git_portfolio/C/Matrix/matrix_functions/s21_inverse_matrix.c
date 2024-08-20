#include "./../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = S21_SUCCES;
  if (s21_check_matrix(A)) {
    flag = UNCORRECT_MATRIX;
  } else if (A->rows == 1) {
    flag = s21_create_matrix(A->rows, A->rows, result);
    if (flag == 0) result->matrix[0][0] = 1.0 / A->matrix[0][0];
  } else {
    double deter = 0.0;
    flag = s21_determinant(A, &deter);
    if (deter == 0 || flag != S21_SUCCES) {
      flag = ERROR;
    } else {
      matrix_t calc = {0};
      flag = s21_calc_complements(A, &calc);
      if (flag == S21_SUCCES) {
        matrix_t trans = {0};
        flag = s21_transpose(&calc, &trans);
        if (flag == S21_SUCCES) {
          flag = s21_mult_number(&trans, 1 / deter, result);
        }
        s21_remove_matrix(&trans);
      }
      s21_remove_matrix(&calc);
    }
  }
  return flag;
}