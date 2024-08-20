#include "../s21_test_decimal.h"

START_TEST(test_s21_is_less_1) {
  // тест 1
  s21_decimal decimal_1, decimal_2;
  decimal_1 = s21_decimal_null();
  decimal_2 = s21_decimal_null();

  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_FALSE);
}
END_TEST

START_TEST(test_s21_is_less_2) {
  // тест 2
  s21_decimal decimal_1, decimal_2;
  decimal_1 = s21_decimal_null();
  decimal_2 = s21_decimal_null();
  decimal_2 = s21_decimal_set_bit(decimal_2, 10, 1);

  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_TRUE);
}
END_TEST

START_TEST(test_s21_is_less_3) {
  // тест 3
  s21_decimal decimal_1, decimal_2;
  decimal_1 = s21_decimal_null();
  decimal_2 = s21_decimal_null();
  decimal_1 = s21_decimal_set_bit(decimal_1, 127, 1);

  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_FALSE);
}
END_TEST

START_TEST(test_s21_is_less_4) {
  // тест 4
  s21_decimal decimal_1, decimal_2;
  decimal_1 = s21_decimal_null();
  decimal_2 = s21_decimal_null();
  decimal_2 = s21_decimal_set_bit(decimal_2, 95, 1);

  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_TRUE);
}
END_TEST

START_TEST(test_s21_is_less_5) {
  // тест 5
  s21_decimal decimal_1, decimal_2;
  decimal_1 = s21_decimal_null();
  decimal_2 = s21_decimal_null();
  decimal_1 = s21_decimal_set_bit(decimal_1, 10, 1);
  decimal_2 = s21_decimal_set_bit(decimal_2, 10, 1);
  decimal_2 = s21_decimal_set_bit(decimal_2, 127, 1);

  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_FALSE);
}
END_TEST

START_TEST(test_s21_is_less_6) {
  s21_decimal decimal_1 = {{50, 50, 0, 0}};
  decimal_1 = s21_decimal_set_scale(decimal_1, 1);
  s21_decimal decimal_2 = {{50, 50, 0, 0}};
  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_TRUE);
}
END_TEST

START_TEST(test_s21_is_less_7) {
  s21_decimal decimal_1 = {{0, 0, 0, 0}};
  s21_decimal decimal_2 = {{0, 0, 0, 0}};
  s21_negate(decimal_1, &decimal_1);
  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_FALSE);
}
END_TEST

START_TEST(test_s21_is_less_8) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal_1 = {{0b00101000111101011100001010001111,
                            0b11110101110000101000111101011100,
                            0b10100011110101110000101000, 0}};
  decimal_1 = s21_decimal_set_scale(decimal_1, 1);
  s21_decimal decimal_2 = {{max, max, max, 0}};
  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_TRUE);
}
END_TEST

START_TEST(test_s21_is_less_9) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal_1 = {{max, max, max, 0}};
  s21_decimal decimal_2 = {{max, max, max - 1, 0}};
  s21_negate(decimal_1, &decimal_1);
  s21_negate(decimal_2, &decimal_2);
  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_TRUE);
}
END_TEST

START_TEST(test_s21_is_less_10) {
  int max = 0b11111111111111111111111111111111;
  s21_decimal decimal_1 = {{max, max, 0, 0}};
  s21_decimal decimal_2 = {{max, max, max, 0}};
  s21_negate(decimal_1, &decimal_1);
  s21_negate(decimal_2, &decimal_2);
  int result_s21_is_less = s21_is_less(decimal_1, decimal_2);
  ck_assert_int_eq(result_s21_is_less, S21_FALSE);
}
END_TEST

Suite *test_s21_is_less_suite() {
  // создаем новый набор для тестов функции
  Suite *suite = suite_create("s21_is_less");
  TCase *tc_core = tcase_create("core_of_s21_is_less");

  // каждый тест добавляем
  tcase_add_test(tc_core, test_s21_is_less_1);
  tcase_add_test(tc_core, test_s21_is_less_2);
  tcase_add_test(tc_core, test_s21_is_less_3);
  tcase_add_test(tc_core, test_s21_is_less_4);
  tcase_add_test(tc_core, test_s21_is_less_5);
  tcase_add_test(tc_core, test_s21_is_less_6);
  tcase_add_test(tc_core, test_s21_is_less_7);
  tcase_add_test(tc_core, test_s21_is_less_8);
  tcase_add_test(tc_core, test_s21_is_less_9);
  tcase_add_test(tc_core, test_s21_is_less_10);
  // тест кейс добавляем в suite
  suite_add_tcase(suite, tc_core);
  return suite;
}