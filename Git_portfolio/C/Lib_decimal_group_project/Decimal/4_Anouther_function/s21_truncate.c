#include "./../../Headers/s21_another_function.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = S21_ANFUNC_SUCCESS;

  if (result != NULL && s21_decimal_is_correct(value)) {
    s21_BigData val = s21_BDecimal_get_data(value);
    for (int i = val.scale; i > 0; i--) {
      s21_BDecimal_div_10(&val);
    }
    *result = s21_BDecimal_set_data(val);
  } else {
    flag = S21_ANFUNC_ERROR;
  }
  return flag;
}