#include "../s21_test_matrix.h"

START_TEST(test_s21_determinant_1) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) m.matrix[i][j] = j;
  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(code, S21_SUCCES);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_s21_determinant_2) {
  const int size = 5;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][1] = 6;
  m.matrix[0][2] = -2;
  m.matrix[0][3] = -1;
  m.matrix[0][4] = 5;
  m.matrix[1][3] = -9;
  m.matrix[1][4] = -7;
  m.matrix[2][1] = 15;
  m.matrix[2][2] = 35;
  m.matrix[3][1] = -1;
  m.matrix[3][2] = -11;
  m.matrix[3][3] = -2;
  m.matrix[3][4] = 1;
  m.matrix[4][0] = -2;
  m.matrix[4][1] = -2;
  m.matrix[4][2] = 3;
  m.matrix[4][4] = -2;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, 2480, 0.000001);
  ck_assert_int_eq(code, S21_SUCCES);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_s21_determinant_3) {
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
      m1.matrix[i][j] = -i;
      m2.matrix[i][j] = -j;
      result.matrix[i][j] = -i - j;
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

START_TEST(test_s21_determinant_4) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);
  m.matrix[0][0] = 2;
  m.matrix[0][1] = 3;
  m.matrix[0][2] = 1;
  m.matrix[1][0] = 7;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 1;
  m.matrix[2][0] = 9;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = 1;

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_double_eq_tol(res, -32, 1e-6);
  ck_assert_int_eq(code, S21_SUCCES);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_s21_determinant_5) {
  matrix_t m = {0};
  s21_create_matrix(5, 4, &m);

  double res = 0;
  int code = s21_determinant(&m, &res);
  ck_assert_int_eq(code, ERROR);

  s21_remove_matrix(&m);
}
END_TEST

Suite *test_s21_determinant_suite() {
  Suite *suite = suite_create("s21_determinant");
  TCase *tc_core = tcase_create("core_of_s21_determinant");

  tcase_add_test(tc_core, test_s21_determinant_1);
  tcase_add_test(tc_core, test_s21_determinant_2);
  tcase_add_test(tc_core, test_s21_determinant_3);
  tcase_add_test(tc_core, test_s21_determinant_4);
  tcase_add_test(tc_core, test_s21_determinant_5);

  suite_add_tcase(suite, tc_core);

  return suite;
}