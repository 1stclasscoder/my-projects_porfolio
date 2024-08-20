#ifndef S21_DEC_FUNC
#define S21_DEC_FUNC

/*--------------------------------HEADERS-------------------------------*/

#include "./s21_binary_function.h"
#include "./s21_decimal_types.h"

/*----------------------------Decimal function---------------------------*/

/**
 * @brief Функция по созданию нулевого числа decimal
 * @return нулевую переменную decimal
 */
s21_decimal s21_decimal_null();

/**
 * @brief Функция для проверки равно ли число нулевому decimal
 * @param value проверяемая переменная
 * @return
 * 1 - если число равно нулю;
 * 0 - если число не равно нулю.
 */
bit32_t s21_decimal_is_null(s21_decimal value);

/**
 * @brief Функция по инверсии мантисы числа типа decimal
 * @param value инвертируемое число типа decimal
 * @return инверсию числа value
 */
s21_decimal s21_decimal_invert(s21_decimal value, bit32_t count);

/**
 * @brief Функция по сдвигу мантисы влево на 1 бит
 * @param value исходное число типа decimal
 * @return число со сдвинутой мантисой влево
 */
s21_decimal s21_decimal_lshift(s21_decimal value);

/**
 * @brief Функция по сдвигу мантисы вправо на 1 бит
 * @param value исходное число типа decimal
 * @return число со сдвинутой мантисой вправо
 */
s21_decimal s21_decimal_rshift(s21_decimal value);

/**
 * @brief Функция по сдвигу мантисы влево на count битов
 * @param value исходное число типа decimal
 * @param count число на которое необходимо сдвинуть мантису
 * @return число со сдвинутой мантисой на count битов влево
 */
s21_decimal s21_decimal_lshift_count(s21_decimal value, bit32_t count);

/**
 * @brief Функция по сдвигу мантисы вправо на count битов
 * @param value исходное число типа decimal
 * @param count число на которое необходимо сдвинуть мантису
 * @return число со сдвинутой мантисой на count битов вправо
 */
s21_decimal s21_decimal_rshift_count(s21_decimal value, bit32_t count);

bit32_t s21_check_null_stack(s21_decimal value);

/**
 * @brief Функция по проверке на коректное заполнение части DATA числа
 * decimal
 * @param value число типа decimal
 * @return
 * 0 - если число не корректное
 * 1 - если число корректное
 */
bit32_t s21_decimal_is_correct(s21_decimal value);

s21_DecData s21_decimal_null_data();

s21_DecData s21_decimal_get_data(s21_decimal value);

s21_decimal s21_decimal_set_data(s21_DecData data);

/*----------------------------Big Decimal function---------------------------*/
s21_BigData s21_BDecimal_null_data();

bit32_t s21_BDecimal_is_null(s21_BigData value);

s21_BigData s21_BDecimal_invert(s21_BigData value, bit32_t count);

s21_BigData s21_BDecimal_lshift(s21_BigData value);

s21_BigData s21_BDecimal_lshift_count(s21_BigData value, bit32_t count);

s21_BigData s21_BDecimal_rshift(s21_BigData value);

s21_BigData s21_BDecimal_get_data(s21_decimal value);

s21_decimal s21_BDecimal_set_data(s21_BigData data);

// void print_decimal(s21_decimal value, char* name);

// void print_dec_data(s21_BigData data, char* name);

#endif