#include "./../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;
  if (s21_check_matrix(A) || s21_check_matrix(B)) {
    flag = FAILURE;
  } else if (s21_equal_columns_rows(A, B)) {
    flag = FAILURE;
  } else {
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*A).columns; ++j) {
        if (round((*A).matrix[i][j] * pow(10, 7)) !=
            round((*B).matrix[i][j] * pow(10, 7))) {
          flag = FAILURE;
        }
      }
    }
  }
  return flag;
}