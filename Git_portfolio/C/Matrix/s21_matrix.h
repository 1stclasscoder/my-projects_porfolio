#ifndef S21_MATRIX
#define S21_MATRIX

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

enum s21_matrix_result {
  S21_SUCCES = 0,
  UNCORRECT_MATRIX = 1,
  ERROR = 2,
};

enum s21_matrix_compare {
  SUCCESS = 1,
  FAILURE = 0,
};

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void s21_minor_matrix(int A_rows, int A_columns, matrix_t *A, matrix_t *minor);
int s21_equal_columns_rows(matrix_t *A, matrix_t *B);
int s21_check_matrix(matrix_t *Z);
int s21_calc_complements(matrix_t *A, matrix_t *result);
double s21_count_determinant(matrix_t *A);
#endif