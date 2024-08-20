#include "./../s21_matrix.h"

double s21_count_determinant(matrix_t *A) {
  double deter = 0.0;
  if (A->rows == 1) {
    deter = A->matrix[0][0];
  } else {
    matrix_t minor = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
    for (int j = 0; j < A->columns; ++j) {
      s21_minor_matrix(0, j, A, &minor);
      if (j % 2) {
        deter -= A->matrix[0][j] * s21_count_determinant(&minor);
      } else {
        deter += A->matrix[0][j] * s21_count_determinant(&minor);
      }
    }
    s21_remove_matrix(&minor);
  }
  return deter;
}