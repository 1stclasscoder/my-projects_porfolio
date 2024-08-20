#include "./../../Headers/s21_convertation_and_parsers.h"

// hernya
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error_code = S21_CONV_SUCCESS;
  if (dst == NULL || !s21_decimal_is_correct(src)) {
    error_code = S21_CONV_ERROR;
  } else if (s21_decimal_is_null(src)) {
    if (s21_decimal_get_sign(src)) {
      *dst = -0.0;
    } else {
      *dst = 0.0;
    }
  } else {
    *dst = 0.0;
    double tmp = 0.0;
    int sign = s21_decimal_get_sign(src);
    int scale = s21_decimal_get_scale(src);
    for (int i = 0; i < SIZE_BLOCK * 3; i++) {
      if (s21_decimal_get_bit(src, i) != 0) {
        tmp += pow(2.0, i);
      }
    }
    tmp = tmp / pow(10, scale);
    if (sign) {
      tmp *= -1;
    }
    *dst = (float)tmp;
  }
  return error_code;
}