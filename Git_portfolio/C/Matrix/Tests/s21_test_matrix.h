#include <check.h>
#include <stdlib.h>

#include "./../s21_matrix.h"

Suite *test_s21_create_matrix_suite();
Suite *test_s21_remove_matrix_suite();
Suite *test_s21_eq_matrix_suite();
Suite *test_s21_sum_matrix_suite();
Suite *test_s21_sub_matrix_suite();
Suite *test_s21_mult_number_suite();
Suite *test_s21_mult_matrix_suite();
Suite *test_s21_transpose_suite();
Suite *test_s21_calc_complements_suite();
Suite *test_s21_determinant_suite();
Suite *test_s21_inverse_matrix_suite();

// функция для прогона набора тестов
unsigned int run_suite(Suite *suite, char *file_logs);
