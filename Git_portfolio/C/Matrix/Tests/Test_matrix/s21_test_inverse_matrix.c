#include "../s21_test_matrix.h"

START_TEST(test_s21_inverse_matrix_1) {
  matrix_t A, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B;
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_s21_inverse_matrix_2) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    m.matrix[0][0] = 1431.12312331;
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(result.matrix[0][0] == (1.0 / m.matrix[0][0]), 1);
    ck_assert_int_eq(code, S21_SUCCES);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(test_s21_inverse_matrix_3) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, UNCORRECT_MATRIX);
}
END_TEST

START_TEST(test_s21_inverse_matrix_4) {
  const int size = 2;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 1;
  m.matrix[0][1] = 1;
  m.matrix[1][0] = 1;
  m.matrix[1][1] = 1;

  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, ERROR);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_s21_inverse_matrix_5) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_create_matrix(5, 2, &m);
  code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, ERROR);
  s21_remove_matrix(&m);
}
END_TEST

Suite *test_s21_inverse_matrix_suite() {
  Suite *suite = suite_create("s21_inverse_matrix");
  TCase *tc_core = tcase_create("core_of_s21_inverse_matrix");

  tcase_add_test(tc_core, test_s21_inverse_matrix_1);
  tcase_add_test(tc_core, test_s21_inverse_matrix_2);
  tcase_add_test(tc_core, test_s21_inverse_matrix_3);
  tcase_add_test(tc_core, test_s21_inverse_matrix_4);
  tcase_add_test(tc_core, test_s21_inverse_matrix_5);
  suite_add_tcase(suite, tc_core);

  return suite;
}