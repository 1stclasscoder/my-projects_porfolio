#include "../s21_test_matrix.h"

START_TEST(test_s21_mult_number_1) {
  matrix_t *A = NULL;
  matrix_t result;
  double num = 5;

  int error_code = s21_mult_number(A, num, &result);

  ck_assert_int_eq(error_code, UNCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_mult_number_2) {
  const int rows = 3;
  const int cols = 3;
  matrix_t m = {0};
  matrix_t result = {0};
  matrix_t my_result = {0};
  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(rows, cols, &result);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = i * cols + j;
      result.matrix[i][j] = 0;
    }
  }
  s21_mult_number(&m, 0, &my_result);
  ck_assert_int_eq(s21_eq_matrix(&my_result, &result), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
  s21_remove_matrix(&my_result);
}
END_TEST

Suite *test_s21_mult_number_suite() {
  Suite *suite = suite_create("s21_mult_number");
  TCase *tc_core = tcase_create("core_of_s21_mult_number");

  tcase_add_test(tc_core, test_s21_mult_number_1);
  tcase_add_test(tc_core, test_s21_mult_number_2);

  suite_add_tcase(suite, tc_core);

  return suite;
}