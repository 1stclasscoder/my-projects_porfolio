#include "../s21_test_decimal.h"

START_TEST(test_s21_add_1) {
  s21_decimal a, b;
  s21_from_int_to_decimal(333, &a);
  s21_from_int_to_decimal(222, &b);

  s21_decimal result;
  int error_code = s21_add(a, b, &result);
  ck_assert_int_eq(error_code, S21_SUCCES);

  int int_result = result.bits[0];

  s21_from_decimal_to_int(result, &int_result);
  ck_assert_int_eq(result.bits[0], 555);
}
END_TEST

START_TEST(test_s21_add_2) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(0, &b);

  s21_decimal result;
  int error_code = s21_add(a, b, &result);

  ck_assert_int_eq(error_code, S21_SUCCES);

  int int_result;
  s21_from_decimal_to_int(result, &int_result);

  ck_assert_int_eq(int_result, 0);
}
END_TEST

START_TEST(test_s21_add_3) {
  int int_a = 23445, int_b = 9887;
  s21_decimal a, b;
  s21_from_int_to_decimal(int_a, &a);
  s21_from_int_to_decimal(int_b, &b);

  s21_decimal result;
  int error_code = s21_add(a, b, &result);

  ck_assert_int_eq(error_code, S21_SUCCES);

  int int_result;
  s21_from_decimal_to_int(result, &int_result);

  ck_assert_int_eq(int_result, int_a + int_b);
}
END_TEST

START_TEST(test_s21_add_5) {
  s21_decimal a, b;
  a = s21_decimal_null();
  b = s21_decimal_null();
  a.bits[0] = 0b11111111111111111111111111111111;
  a.bits[1] = 0b11111111111111111111111111111111;
  a.bits[2] = 0b11111111111111111111111111111111;

  b.bits[0] = 0b11111111111111111111111111111111;
  b.bits[1] = 0b11111111111111111111111111111111;
  b.bits[2] = 0b11111111111111111111111111111111;

  s21_decimal result;
  int error_code = s21_add(a, b, &result);

  ck_assert_int_eq(error_code, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_add_6) {
  bit32_t max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, 0, 0}};
  s21_decimal decimal2 = {{max, 0, 0, 0}};
  s21_decimal decimal3 = {{0b11111111111111111111111111111110, 0, 0b1, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_add_7) {
  bit32_t max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, 0, 0}};
  s21_decimal decimal2 = {{max, 0, 0, 0}};
  s21_decimal decimal3 = {{0, max, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal2, &decimal2);
  int check = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_add_8) {
  bit32_t max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{max, max, max, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal1, &decimal1);
  s21_negate(decimal2, &decimal2);
  int check = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_SMALL);
}
END_TEST

START_TEST(test_s21_add_9) {
  bit32_t max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{max, max, max, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  int check = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(check, S21_TOO_LARGE);
}
END_TEST

START_TEST(test_s21_add_10) {
  bit32_t max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, max, 0}};
  s21_decimal decimal2 = {{max, max, max, 0}};
  s21_decimal decimal3 = {{0, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal2, &decimal2);
  int check = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
}
END_TEST

START_TEST(test_s21_add_11) {
  bit32_t max = 0b11111111111111111111111111111111;
  s21_decimal decimal1 = {{max, max, 0, 0}};
  s21_decimal decimal2 = {{max, max, max, 0}};
  s21_decimal decimal3 = {{0, 0, max, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_negate(decimal1, &decimal1);
  int check = s21_add(decimal1, decimal2, &result);
  ck_assert_int_eq(s21_is_equal(result, decimal3), 1);
  ck_assert_int_eq(check, S21_SUCCES);
}
END_TEST

Suite *test_s21_add_suite() {
  Suite *suite = suite_create("s21_add");
  TCase *tc_core = tcase_create("core_of_s21_add");

  tcase_add_test(tc_core, test_s21_add_1);
  tcase_add_test(tc_core, test_s21_add_2);
  tcase_add_test(tc_core, test_s21_add_3);
  tcase_add_test(tc_core, test_s21_add_5);
  tcase_add_test(tc_core, test_s21_add_6);
  tcase_add_test(tc_core, test_s21_add_7);
  tcase_add_test(tc_core, test_s21_add_8);
  tcase_add_test(tc_core, test_s21_add_9);
  tcase_add_test(tc_core, test_s21_add_10);
  tcase_add_test(tc_core, test_s21_add_11);
  suite_add_tcase(suite, tc_core);

  return suite;
}