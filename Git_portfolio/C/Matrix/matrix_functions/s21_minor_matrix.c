
#include "./../s21_matrix.h"

void s21_minor_matrix(int A_rows, int A_columns, matrix_t *A, matrix_t *minor) {
  int minor_rows = 0;
  int minor_columns = 0;
  for (int i = 0; i < (*A).rows; ++i) {
    for (int j = 0; j < (*A).columns; ++j) {
      if (i != A_rows && j != A_columns) {
        minor->matrix[minor_rows][minor_columns] = A->matrix[i][j];
        ++minor_columns;

        if (minor_columns >= minor->columns) {
          ++minor_rows;
          minor_columns = 0;
        }
      }
    }
  }
}