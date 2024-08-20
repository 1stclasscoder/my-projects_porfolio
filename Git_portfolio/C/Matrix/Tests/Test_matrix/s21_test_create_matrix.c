#include "../s21_test_matrix.h"

START_TEST(test_s21_create_matrix_1) {
  matrix_t A;
  int result = s21_create_matrix(100, 200, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(result, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_create_matrix_2) {
  matrix_t A;
  int result = s21_create_matrix(1483647, 10, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(result, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_create_matrix_3) {
  matrix_t A = {0};
  int result = s21_create_matrix(0, 2, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(result, UNCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_create_matrix_4) {
  matrix_t A = {0};
  int result = s21_create_matrix(3, 0, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(result, UNCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_create_matrix_5) {
  matrix_t A;
  int result = s21_create_matrix(33, 10, &A);
  s21_remove_matrix(&A);
  ck_assert_int_eq(result, S21_SUCCES);
}
END_TEST

Suite *test_s21_create_matrix_suite() {
  Suite *suite = suite_create("s21_create_matrix");
  TCase *tc_core = tcase_create("core_of_s21_create_matrix");

  tcase_add_test(tc_core, test_s21_create_matrix_1);
  tcase_add_test(tc_core, test_s21_create_matrix_2);
  tcase_add_test(tc_core, test_s21_create_matrix_3);
  tcase_add_test(tc_core, test_s21_create_matrix_4);
  tcase_add_test(tc_core, test_s21_create_matrix_5);

  suite_add_tcase(suite, tc_core);

  return suite;
}