#include "./../../Headers/s21_another_function.h"
#include "./../../Headers/s21_convertation_and_parsers.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error_code = S21_CONV_SUCCESS;
  if (dst == NULL || !s21_decimal_is_correct(src)) {
    error_code = S21_CONV_ERROR;
  } else {
    s21_truncate(src, &src);
    s21_BigData src_DecData = s21_BDecimal_get_data(src);
    if ((src_DecData.bits[2] || src_DecData.bits[3] || src_DecData.bits[1]) &&
        s21_BDecimal_get_bit(src_DecData, SIZE_BLOCK - 1)) {
      error_code = S21_CONV_ERROR;
      *dst = 0;
    } else {
      if (src_DecData.sign) {
        *dst = (int)src_DecData.bits[0] * (-1);
      } else {
        *dst = (int)src_DecData.bits[0];
      }
    }
  }
  return error_code;
}
