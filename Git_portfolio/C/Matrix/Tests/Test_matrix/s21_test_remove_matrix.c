#include "../s21_test_matrix.h"

START_TEST(test_s21_remove_matrix_1) {
  matrix_t A;
  s21_create_matrix(20, 25, &A);
  s21_remove_matrix(&A);
  int result = S21_SUCCES;
  if (A.matrix) result = ERROR;
  ck_assert_int_eq(result, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_remove_matrix_2) {
  matrix_t A = {0};
  s21_create_matrix(1483647, 10, &A);
  s21_remove_matrix(&A);
  int result = S21_SUCCES;
  if (A.matrix) result = ERROR;
  ck_assert_int_eq(result, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_remove_matrix_3) {
  matrix_t A;
  s21_create_matrix(4, 3, &A);
  s21_remove_matrix(&A);
  int result = S21_SUCCES;
  if (A.matrix) result = ERROR;
  ck_assert_int_eq(result, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_remove_matrix_4) {
  int result = 0;
  matrix_t A = {0};

  result = s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    result = ERROR;
  }
  ck_assert_int_eq(result, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_remove_matrix_5) {
  int result = 0;
  matrix_t A = {0};

  result = s21_create_matrix(3, 2, &A);
  s21_remove_matrix(&A);
  if (A.matrix != NULL) {
    result = ERROR;
  }
  ck_assert_int_eq(result, S21_SUCCES);
}
END_TEST

Suite *test_s21_remove_matrix_suite() {
  Suite *suite = suite_create("s21_remove_matrix");
  TCase *tc_core = tcase_create("core_of_s21_remove_matrix");

  tcase_add_test(tc_core, test_s21_remove_matrix_1);
  tcase_add_test(tc_core, test_s21_remove_matrix_2);
  tcase_add_test(tc_core, test_s21_remove_matrix_3);
  tcase_add_test(tc_core, test_s21_remove_matrix_4);
  tcase_add_test(tc_core, test_s21_remove_matrix_5);

  suite_add_tcase(suite, tc_core);

  return suite;
}