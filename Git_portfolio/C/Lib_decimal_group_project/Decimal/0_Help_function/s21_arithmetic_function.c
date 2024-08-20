#include "./../../Headers/s21_help_function.h"

// работает

void s21_BDecimal_normalize(s21_BigData *value_1, s21_BigData *value_2) {
  if (value_1->scale > value_2->scale) {
    bit32_t count_scale = value_1->scale - value_2->scale;
    s21_BDecimal_count_mul_10(value_2, count_scale);
  } else if (value_1->scale < value_2->scale) {
    bit32_t count_scale = value_2->scale - value_1->scale;
    s21_BDecimal_count_mul_10(value_1, count_scale);
  }
}

void s21_BDecimal_add_mantis(s21_BigData value_1, s21_BigData value_2,
                             s21_BigData *result) {
  bit_t bit = 0;  // переходный бит
  s21_BigData new = s21_BDecimal_null_data();
  for (bit32_t i = 0; i < s21_max(value_1.high_bit, value_2.high_bit); i++) {
    bit = s21_BDecimal_get_bit(value_1, i) + s21_BDecimal_get_bit(value_2, i) +
          s21_BDecimal_get_bit(new, i);
    new = s21_BDecimal_set_bit(new, i, bit % 2);
    if (bit / 2) {
      new = s21_BDecimal_set_bit(new, i + 1, bit / 2);
    }
  }
  for (int i = 0; i < COUNT_BLOCKS_BD; i++) {
    result->bits[i] = new.bits[i];
  }
  if (value_1.scale == value_2.scale) {
    result->scale = value_1.scale;
  } else {
  }
  result->high_bit = s21_BDecimal_get_high_bit(*result);
}

void s21_BDecimal_sub_mantis(s21_BigData value_1, s21_BigData value_2,
                             s21_BigData *result) {
  s21_BigData new = s21_BDecimal_null_data();
  // инвертируем число
  value_1 = s21_BDecimal_invert(value_1, COUNT_BLOCKS_BD);
  value_1.high_bit = s21_BDecimal_get_high_bit(value_1);
  // выполняем суммирование
  s21_BDecimal_add_mantis(value_1, value_2, &new);
  // инвертируем обратно
  new = s21_BDecimal_invert(new, COUNT_BLOCKS_BD);
  for (int i = 0; i < COUNT_BLOCKS_BD; i++) {
    result->bits[i] = new.bits[i];
  }
  if (value_1.scale == value_2.scale) {
    result->scale = value_1.scale;
  }
  result->high_bit = s21_BDecimal_get_high_bit(*result);
}

void s21_BDecimal_mul_mantis(s21_BigData value_1, s21_BigData value_2,
                             s21_BigData *result) {
  s21_BigData new = s21_BDecimal_null_data();
  // проверка для наименьшего цикла выполения умножения
  if (value_1.high_bit < value_2.high_bit) {
    for (bit32_t i = 0; i < value_1.high_bit; i++) {
      if (s21_BDecimal_get_bit(value_1, i)) {
        s21_BDecimal_add_mantis(new, value_2, &new);
      }
      value_2 = s21_BDecimal_lshift(value_2);
    }
  } else {
    for (bit32_t i = 0; i < value_2.high_bit; i++) {
      if (s21_BDecimal_get_bit(value_2, i)) {
        s21_BDecimal_add_mantis(new, value_1, &new);
      }
      value_1 = s21_BDecimal_lshift(value_1);
    }
  }
  for (int i = 0; i < COUNT_BLOCKS_BD; i++) {
    result->bits[i] = new.bits[i];
  }
  result->high_bit = s21_BDecimal_get_high_bit(*result);
}

s21_BigData s21_BDecimal_div_mantis(s21_BigData value_1, s21_BigData value_2,
                                    s21_BigData *result) {
  s21_BigData new = s21_BDecimal_null_data();
  bit32_t shift = value_1.high_bit - value_2.high_bit;
  if ((int)shift >= 0) {
    value_2 = s21_BDecimal_lshift_count(value_2, shift);
    bit32_t result_comp = 0;
    while ((int)shift >= 0) {
      result_comp = s21_BDecimal_compare_mantis(value_1, value_2);
      if (result_comp == 2) {
        new = s21_BDecimal_set_bit(new, shift, 0);
      } else {
        s21_BDecimal_sub_mantis(value_1, value_2, &value_1);
        new = s21_BDecimal_set_bit(new, shift, 1);
      }
      if (shift != 0) {
        value_2 = s21_BDecimal_rshift(value_2);
      }
      shift--;
    }
  }
  for (int i = 0; i < COUNT_BLOCKS_BD; i++) {
    result->bits[i] = new.bits[i];
  }
  result->high_bit = s21_BDecimal_get_high_bit(*result);
  return value_1;
}

bit32_t s21_BDecimal_basic_add(s21_BigData value_1, s21_BigData value_2,
                               s21_BigData *result) {
  bit32_t error_code = S21_SUCCES;
  if (value_1.scale != value_2.scale) {
    s21_BDecimal_normalize(&value_1, &value_2);
  }
  if (value_1.sign == value_2.sign) {
    result->sign = value_1.sign;
    s21_BDecimal_add_mantis(value_1, value_2, result);
  } else {
    bit32_t result_compare = s21_BDecimal_compare_mantis(value_1, value_2);
    if (result_compare == 1) {
      result->sign = value_1.sign;
      s21_BDecimal_sub_mantis(value_1, value_2, result);
    } else if (result_compare == 2) {
      result->sign = value_2.sign;
      s21_BDecimal_sub_mantis(value_2, value_1, result);
    } else {
      *result = s21_BDecimal_null_data();
    }
  }
  error_code = s21_BDecimal_check_result(result);
  if (error_code != S21_SUCCES) {
    *result = s21_BDecimal_null_data();
  }
  return error_code;
}

bit32_t s21_BDecimal_basic_sub(s21_BigData value_1, s21_BigData value_2,
                               s21_BigData *result) {
  bit32_t error_code = S21_SUCCES;
  if (value_1.scale != value_2.scale) {
    s21_BDecimal_normalize(&value_1, &value_2);
  }
  if (value_1.sign == value_2.sign) {
    bit32_t result_compare = s21_BDecimal_compare_mantis(value_1, value_2);
    if (result_compare == 1) {
      s21_BDecimal_sub_mantis(value_1, value_2, result);
      result->sign = value_1.sign;
    } else if (result_compare == 2) {
      s21_BDecimal_sub_mantis(value_2, value_1, result);
      result->sign = !value_2.sign;
    } else {
      *result = s21_BDecimal_null_data();
    }
  } else {
    s21_BDecimal_add_mantis(value_1, value_2, result);
    result->sign = value_1.sign;
  }
  error_code = s21_BDecimal_check_result(result);
  if (error_code != S21_SUCCES) {
    *result = s21_BDecimal_null_data();
  }
  return error_code;
}

bit32_t s21_BDecimal_basic_mul(s21_BigData value_1, s21_BigData value_2,
                               s21_BigData *result) {
  bit32_t error_code = S21_SUCCES;
  result->sign = value_1.sign == value_2.sign ? 0 : 1;
  result->scale = value_1.scale + value_2.scale;
  s21_BDecimal_mul_mantis(value_1, value_2, result);
  error_code = s21_BDecimal_check_result(result);
  if (error_code != S21_SUCCES) {
    *result = s21_BDecimal_null_data();
  }
  return error_code;
}

bit32_t s21_BDecimal_basic_div(s21_BigData value_1, s21_BigData value_2,
                               s21_BigData *result) {
  bit32_t error_code = S21_SUCCES;
  int free_bit = SIZE_MANTIS - value_1.high_bit;
  if (free_bit > 0) {
    bit32_t count_mul = free_bit / 3 + (free_bit % 3 != 0);
    s21_BDecimal_count_mul_10(&value_1, count_mul);
  }
  result->scale = value_1.scale - value_2.scale;
  result->sign = value_1.sign == value_2.sign ? 0 : 1;
  s21_BigData residue = s21_BDecimal_div_mantis(value_1, value_2, result);
  if (s21_BDecimal_is_null(residue)) {
    s21_BDecimal_bank_round_data(result, value_2, residue);
  }
  error_code = s21_BDecimal_check_result(result);
  if (error_code != S21_SUCCES) {
    *result = s21_BDecimal_null_data();
  }
  return error_code;
}

bit32_t s21_max(bit32_t val_1, bit32_t val_2) {
  return val_1 > val_2 ? val_1 : val_2;
}

void s21_BDecimal_mul_10(s21_BigData *value) {
  s21_BigData ten = s21_BDecimal_null_data();
  ten.bits[0] = 10;
  ten.high_bit = s21_BDecimal_get_high_bit(ten);
  s21_BigData new = s21_BDecimal_null_data();
  new.scale = value->scale;
  new.sign = value->sign;
  s21_BDecimal_mul_mantis(*value, ten, &new);
  for (int i = 0; i <= COUNT_BLOCKS_BD; i++) {
    value->bits[i] = new.bits[i];
  }
  value->high_bit = s21_BDecimal_get_high_bit(*value);
  value->sign = new.sign;
  value->scale++;
}

s21_BigData s21_BDecimal_div_10(s21_BigData *value) {
  s21_BigData ten = s21_BDecimal_null_data();
  ten.bits[0] = 10;
  ten.high_bit = s21_BDecimal_get_high_bit(ten);
  s21_BigData new = s21_BDecimal_null_data();
  new.sign = value->sign;
  s21_BigData residue = s21_BDecimal_div_mantis(*value, ten, &new);
  for (int i = 0; i <= COUNT_BLOCKS_BD; i++) {
    value->bits[i] = new.bits[i];
  }
  value->high_bit = s21_BDecimal_get_high_bit(*value);
  value->scale--;
  return residue;
}

// возвращает количество удавшихся умножений
void s21_BDecimal_count_mul_10(s21_BigData *value, bit32_t count) {
  for (bit32_t i = 0; i < count; i++) {
    s21_BDecimal_mul_10(value);
  }
}

bit32_t s21_BDecimal_count_div_10(s21_BigData *value, bit32_t count) {
  bit32_t error_code = S21_SUCCES;
  s21_BigData residue = s21_BDecimal_null_data();
  if (count != 0) {
    for (bit32_t i = 0; i < count - 1; i++) {
      s21_BDecimal_div_10(value);
    }
    residue = s21_BDecimal_div_10(value);
    s21_BDecimal_bank_ten_round_data(value, residue);
  }
  return error_code;
}

bit32_t s21_BDecimal_bank_round_data(s21_BigData *num, s21_BigData divider,
                                     s21_BigData residue) {
  bit_t error_code = S21_SUCCES;
  residue = s21_BDecimal_lshift(residue);
  bit_t res = s21_BDecimal_compare_mantis(residue, divider);
  if (s21_BDecimal_get_bit(*num, 0)) {
    if (res != 2) {
      error_code = s21_BDecimal_add_one(*num, num);
    }
  } else {
    if (res == 1) {
      error_code = s21_BDecimal_add_one(*num, num);
    }
  }
  return error_code;
}

bit32_t s21_BDecimal_add_one(s21_BigData value, s21_BigData *result) {
  bit_t error_code = S21_SUCCES;
  s21_BigData new = s21_BDecimal_null_data();
  new.bits[0] = 1;
  new.high_bit = 0;
  new.sign = value.sign;
  new.scale = value.scale;
  if (!s21_BDecimal_is_null(value)) {
    s21_BDecimal_add_mantis(new, value, &new);
  }
  for (int i = 0; i <= COUNT_BLOCKS_BD; i++) {
    result->bits[i] = new.bits[i];
  }
  result->high_bit = s21_BDecimal_get_high_bit(new);
  result->scale = new.scale;
  result->sign = new.sign;
  return error_code;
}

bit32_t s21_BDecimal_compare_residue_10(s21_BigData residue) {
  s21_BigData five = s21_BDecimal_null_data();
  five.bits[0] = 5;
  five.high_bit = s21_BDecimal_get_high_bit(five);
  return s21_BDecimal_compare_mantis(residue, five);
}

bit32_t s21_BDecimal_bank_ten_round_data(s21_BigData *num,
                                         s21_BigData residue) {
  bit_t error_code = S21_SUCCES;
  bit_t res = s21_BDecimal_compare_residue_10(residue);
  if (s21_BDecimal_get_bit(*num, 0)) {
    if (res != 2) {
      s21_BDecimal_add_one(*num, num);
    }
  } else {
    if (res == 1) {
      s21_BDecimal_add_one(*num, num);
    }
  }
  return error_code;
}

bit32_t s21_BDecimal_check_result(s21_BigData *result) {
  bit32_t error_code = S21_SUCCES;
  if (result->scale >= MAX_SCALE) {
    if (result->high_bit > (bit32_t)3 * result->scale) {
      s21_BDecimal_count_div_10(result, result->scale - MAX_SCALE);
    } else {
      *result = s21_BDecimal_null_data();
    }
  }
  if (result->high_bit > SIZE_MANTIS) {
    if (result->scale >= MIN_SCALE) {
      s21_BigData residue = s21_BDecimal_null_data();
      while ((result->bits[6] || result->bits[5] || result->bits[4] ||
              result->bits[3]) &&
             result->scale > 0) {
        residue = s21_BDecimal_div_10(result);
        s21_BDecimal_bank_ten_round_data(result, residue);
      }
    } else {
      if (result->sign) {
        error_code = S21_TOO_SMALL;
      } else {
        error_code = S21_TOO_LARGE;
      }
    }
  }
  if (result->scale < MIN_SCALE || result->bits[6] || result->bits[5] ||
      result->bits[4] || result->bits[3]) {
    if (result->sign) {
      error_code = S21_TOO_SMALL;
    } else {
      error_code = S21_TOO_LARGE;
    }
  }
  return error_code;
}
