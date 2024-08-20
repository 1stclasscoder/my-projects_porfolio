#include "./../../Headers/s21_another_function.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  bit32_t error_code = S21_ANFUNC_SUCCESS;
  error_code = s21_truncate(value, result);
  if (!error_code) {
    s21_BigData val = s21_BDecimal_get_data(value);
    if (val.scale && val.sign) {
      s21_BigData res = s21_BDecimal_get_data(*result);
      res.sign = val.sign;
      s21_BDecimal_count_mul_10(&res, val.scale);
      s21_BDecimal_sub_mantis(val, res, &val);
      s21_BDecimal_count_div_10(&res, val.scale);
      if (!s21_BDecimal_is_null(val)) {
        error_code = s21_BDecimal_add_one(res, &res);
      }
      *result = s21_BDecimal_set_data(res);
    }
  } else {
    *result = s21_decimal_null();
  }
  return error_code;
}