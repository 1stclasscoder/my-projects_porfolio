#include "../s21_test_matrix.h"

START_TEST(test_s21_calc_complements_1) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, ERROR);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_s21_calc_complements_2) {
  matrix_t m = {0};
  matrix_t result = {0};
  int res = s21_calc_complements(&m, &result);
  ck_assert_int_eq(res, UNCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_calc_complements_3) {
  matrix_t A, result, expected_result;
  int rows = 3, columns = 3;

  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &expected_result);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  expected_result.matrix[0][0] = 0;
  expected_result.matrix[0][1] = 10;
  expected_result.matrix[0][2] = -20;

  expected_result.matrix[1][0] = 4;
  expected_result.matrix[1][1] = -14;
  expected_result.matrix[1][2] = 8;

  expected_result.matrix[2][0] = -8;
  expected_result.matrix[2][1] = -2;
  expected_result.matrix[2][2] = 4;

  int res = s21_calc_complements(&A, &result);
  int result_compare = s21_eq_matrix(&result, &expected_result);

  ck_assert_int_eq(res, S21_SUCCES);
  ck_assert_int_eq(result_compare, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected_result);
}
END_TEST

Suite *test_s21_calc_complements_suite() {
  Suite *suite = suite_create("s21_calc_complements");
  TCase *tc_core = tcase_create("core_of_s21_calc_complements");

  tcase_add_test(tc_core, test_s21_calc_complements_1);
  tcase_add_test(tc_core, test_s21_calc_complements_2);
  tcase_add_test(tc_core, test_s21_calc_complements_3);

  suite_add_tcase(suite, tc_core);

  return suite;
}