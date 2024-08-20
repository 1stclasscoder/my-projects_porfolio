#include "../s21_test_matrix.h"

START_TEST(test_s21_sub_matrix_1) {
  const int rows1 = 3;
  const int cols1 = 3;
  const int rows2 = 2;
  const int cols2 = 2;
  matrix_t m1 = {0};
  matrix_t m2 = {0};
  s21_create_matrix(rows1, cols1, &m1);
  s21_create_matrix(rows2, cols2, &m2);
  matrix_t sub = {0};
  int status = s21_sub_matrix(&m1, &m2, &sub);
  ck_assert_int_eq(status, ERROR);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&sub);
}
END_TEST

START_TEST(test_s21_sub_matrix_2) {
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
      result.matrix[i][j] = i - j;
    }
  }
  matrix_t sub = {0};
  s21_sub_matrix(&m1, &m2, &sub);
  ck_assert_int_eq(s21_eq_matrix(&sub, &result), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&sub);
}
END_TEST

Suite *test_s21_sub_matrix_suite() {
  Suite *suite = suite_create("s21_sub_matrix");
  TCase *tc_core = tcase_create("core_of_s21_sub_matrix");

  tcase_add_test(tc_core, test_s21_sub_matrix_1);
  tcase_add_test(tc_core, test_s21_sub_matrix_2);

  suite_add_tcase(suite, tc_core);

  return suite;
}