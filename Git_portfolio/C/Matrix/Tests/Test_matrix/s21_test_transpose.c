#include "../s21_test_matrix.h"

START_TEST(test_s21_transpose_1) {
  matrix_t *A = NULL;
  matrix_t result;
  int error_code = s21_transpose(A, &result);
  ck_assert_int_eq(error_code, UNCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_transpose_2) {
  const int rows = 3;
  const int cols = 3;
  matrix_t m = {0};
  matrix_t result = {0};
  s21_create_matrix(rows, cols, &m);
  s21_create_matrix(cols, rows, &result);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = i * cols + j;
      result.matrix[j][i] = i * cols + j;
    }
  }
  matrix_t transposed = {0};
  s21_transpose(&m, &transposed);
  ck_assert_int_eq(s21_eq_matrix(&transposed, &result), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&result);
  s21_remove_matrix(&transposed);
}
END_TEST

START_TEST(test_s21_transpose_3) {
  matrix_t m = {0};
  matrix_t transposed = {0};
  int status = s21_transpose(NULL, &transposed);
  ck_assert_int_eq(status, 1);
  status = s21_transpose(&m, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

Suite *test_s21_transpose_suite() {
  Suite *suite = suite_create("s21_transpose");
  TCase *tc_core = tcase_create("core_of_s21_transpose");

  tcase_add_test(tc_core, test_s21_transpose_1);
  tcase_add_test(tc_core, test_s21_transpose_2);
  tcase_add_test(tc_core, test_s21_transpose_3);

  suite_add_tcase(suite, tc_core);

  return suite;
}