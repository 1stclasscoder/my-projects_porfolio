#include "./../../Headers/s21_comprasion_function.h"

bit32_t s21_BDecimal_compare_mantis(s21_BigData value_1, s21_BigData value_2) {
  bit32_t flag = 0;
  if (value_1.high_bit == value_2.high_bit) {
    for (int i = value_1.high_bit - 1; i >= 0 && flag == 0; i--) {
      if (s21_BDecimal_get_bit(value_1, i) > s21_BDecimal_get_bit(value_2, i)) {
        flag = 1;
      } else if (s21_BDecimal_get_bit(value_1, i) <
                 s21_BDecimal_get_bit(value_2, i)) {
        flag = 2;
      }
    }
  } else if (value_1.high_bit > value_2.high_bit) {
    flag = 1;
  } else {
    flag = 2;
  }
  return flag;
}

bit32_t s21_function_compare(s21_decimal value_1, s21_decimal value_2) {
  bit32_t result = 0;
  bit_t null_1 = s21_decimal_is_null(value_1);
  bit_t null_2 = s21_decimal_is_null(value_2);
  if (!null_1 && !null_2) {
    s21_BigData val_1 = s21_BDecimal_get_data(value_1);
    s21_BigData val_2 = s21_BDecimal_get_data(value_2);
    if (val_1.sign == val_2.sign) {
      if (val_1.scale != val_2.scale) {
        s21_BDecimal_normalize(&val_1, &val_2);
      }
      result = s21_BDecimal_compare_mantis(val_1, val_2);
      if (val_1.sign) {
        if (result == 1) {
          result = 2;
        } else if (result == 2) {
          result = 1;
        }
      }
    } else {
      result = !val_2.sign * 2 + !val_1.sign;
    }
  } else {
    if (null_1 == null_2) {
      result = 0;
    } else if (!null_1) {
      if (s21_decimal_get_sign(value_1)) {
        result = 2;
      } else {
        result = 1;
      }
    } else {
      if (s21_decimal_get_sign(value_2)) {
        result = 1;
      } else {
        result = 2;
      }
    }
  }
  return result;
}
