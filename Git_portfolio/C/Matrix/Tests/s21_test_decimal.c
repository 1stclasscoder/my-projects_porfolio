#include "s21_test_matrix.h"

unsigned int run_suite(Suite *suite, char *file_logs) {
  // создаем раней
  SRunner *srunner = srunner_create(suite);

  // результаты записываем в файл
  srunner_set_log(srunner, file_logs);
  srunner_run_all(srunner, CK_ENV);
  // кол-во зафейленых тестов
  int count_failed_tests = srunner_ntests_failed(srunner);

  // освобождаем память которая была определена для ранера
  srunner_free(srunner);

  return count_failed_tests;
}

int main() {
  int count_failed_tests = 0;

  count_failed_tests +=
      run_suite(test_s21_create_matrix_suite(), "logs/test_create_matrix.log");
  count_failed_tests +=
      run_suite(test_s21_remove_matrix_suite(), "logs/test_remove_matrix.log");
  count_failed_tests +=
      run_suite(test_s21_eq_matrix_suite(), "logs/test_eq_matrix.log");
  count_failed_tests +=
      run_suite(test_s21_sum_matrix_suite(), "logs/test_sum_matrix.log");
  count_failed_tests +=
      run_suite(test_s21_sub_matrix_suite(), "logs/test_sub_matrix.log");
  count_failed_tests += run_suite(test_s21_mult_number_suite(),
                                  "logs/test_mult_number_matrix.log");
  count_failed_tests +=
      run_suite(test_s21_mult_matrix_suite(), "logs/test_mult_matrix.log");
  count_failed_tests +=
      run_suite(test_s21_transpose_suite(), "logs/test_transpose.log");
  count_failed_tests += run_suite(test_s21_calc_complements_suite(),
                                  "logs/test_calc_complements.log");
  count_failed_tests +=
      run_suite(test_s21_determinant_suite(), "logs/test_determinant.log");
  count_failed_tests += run_suite(test_s21_inverse_matrix_suite(),
                                  "logs/test_inverse_matrix.log");

  return count_failed_tests == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
