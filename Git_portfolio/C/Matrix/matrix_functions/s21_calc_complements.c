#include "./../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = S21_SUCCES;
  if (s21_check_matrix(A)) {
    flag = UNCORRECT_MATRIX;
  } else if (A->rows != A->columns || A->rows == 1) {
    flag = ERROR;
  } else {
    flag = s21_create_matrix(A->rows, A->columns, result);
    if (flag == S21_SUCCES) {
      for (int i = 0; i < (*A).rows; ++i) {
        for (int j = 0; j < (*A).columns; ++j) {
          matrix_t minor = {0};
          flag = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
          s21_minor_matrix(i, j, A, &minor);
          double determinant = 0;
          flag = s21_determinant(&minor, &determinant);
          result->matrix[i][j] = pow(-1, (i + j)) * determinant;
          s21_remove_matrix(&minor);
        }
      }
    }
  }
  return flag;
}