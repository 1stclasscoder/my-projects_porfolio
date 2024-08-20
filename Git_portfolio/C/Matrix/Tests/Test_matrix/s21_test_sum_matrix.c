#include "../s21_test_matrix.h"

START_TEST(test_s21_sum_matrix_1) {
  matrix_t A = {0};
  matrix_t B, result;

  int rows_common = 2, columns_common = 2;

  s21_create_matrix(rows_common, columns_common, &B);

  int error_code = s21_sum_matrix(&A, &B, &result);

  s21_remove_matrix(&B);

  ck_assert_int_eq(error_code, UNCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_sum_matrix_2) {
  const int rows = 3;
  const int cols = 3;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, cols, &m1);
  s21_create_matrix(rows, cols, &m2);
  s21_create_matrix(rows, cols, &result);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = i;
      m2.matrix[i][j] = j;
      result.matrix[i][j] = i + j;
    }
  }
  matrix_t sum = {0};
  s21_sum_matrix(&m1, &m2, &sum);
  ck_assert_int_eq(s21_eq_matrix(&sum, &result), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&sum);
}
END_TEST

START_TEST(test_s21_sum_matrix_3) {
  matrix_t A, B, result;

  int rows_A = 2, columns_A = 3;
  int rows_B = 4, columns_B = 5;

  s21_create_matrix(rows_A, columns_A, &A);
  s21_create_matrix(rows_B, columns_B, &B);

  int res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(res, ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *test_s21_sum_matrix_suite() {
  Suite *suite = suite_create("s21_sum_matrix");
  TCase *tc_core = tcase_create("core_of_s21_sum_matrix");

  tcase_add_test(tc_core, test_s21_sum_matrix_1);
  tcase_add_test(tc_core, test_s21_sum_matrix_2);
  tcase_add_test(tc_core, test_s21_sum_matrix_3);

  suite_add_tcase(suite, tc_core);

  return suite;
}