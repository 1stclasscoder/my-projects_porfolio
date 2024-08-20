#ifndef S21_HELP_FUNC
#define S21_HELP_FUNC

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_function.h"
#include "./s21_decimal_types.h"

/*--------------------------1_Arithmetic_function-----------------------*/

bit32_t s21_BDecimal_basic_add(s21_BigData value_1, s21_BigData value_2,
                               s21_BigData *result);

bit32_t s21_BDecimal_basic_sub(s21_BigData value_1, s21_BigData value_2,
                               s21_BigData *result);

bit32_t s21_BDecimal_basic_mul(s21_BigData value_1, s21_BigData value_2,
                               s21_BigData *result);

bit32_t s21_BDecimal_basic_div(s21_BigData value_1, s21_BigData value_2,
                               s21_BigData *result);

void s21_BDecimal_normalize(s21_BigData *value_1, s21_BigData *value_2);

bit32_t s21_max(bit32_t val_1, bit32_t val_2);

void s21_BDecimal_add_mantis(s21_BigData value_1, s21_BigData value_2,
                             s21_BigData *result);

void s21_BDecimal_sub_mantis(s21_BigData value_1, s21_BigData value_2,
                             s21_BigData *result);

void s21_BDecimal_mul_mantis(s21_BigData value_1, s21_BigData value_2,
                             s21_BigData *result);

s21_BigData s21_BDecimal_div_mantis(s21_BigData value_1, s21_BigData value_2,
                                    s21_BigData *result);
s21_BigData s21_BDecimal_div_mantis(s21_BigData value_1, s21_BigData value_2,
                                    s21_BigData *result);

void s21_BDecimal_mul_10(s21_BigData *value);

s21_BigData s21_BDecimal_div_10(s21_BigData *value);

void s21_BDecimal_count_mul_10(s21_BigData *value, bit32_t count);

bit32_t s21_BDecimal_count_div_10(s21_BigData *value, bit32_t count);

bit32_t s21_BDecimal_bank_round_data(s21_BigData *num, s21_BigData divider,
                                     s21_BigData residue);

bit32_t s21_BDecimal_bank_ten_round_data(s21_BigData *num, s21_BigData residue);

bit32_t s21_BDecimal_add_one(s21_BigData value, s21_BigData *result);

bit32_t s21_BDecimal_check_result(s21_BigData *result);

/*-------------------------2_Comprasion function------------------------*/

bit32_t s21_BDecimal_compare_mantis(s21_BigData value_1, s21_BigData value_2);

bit32_t s21_function_compare(s21_decimal value_1, s21_decimal value_2);

/**
 * @brief функция для сравнения остатка деления на 10 с 5
 * @return если остаток больше возвращает 1, если меньше 2, если равен 0
 */
bit32_t s21_BDecimal_compare_residue_10(s21_BigData residue);
/*------------------3_Convertation_and_parsers_function-----------------*/

/*---------------------------4_Another_function-------------------------*/

// void print_dec_data(s21_BigData data, char *name);
// void print_decimal(s21_decimal data, char *name);
#endif