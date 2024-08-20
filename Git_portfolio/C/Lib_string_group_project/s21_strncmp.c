#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result;
  s21_size_t i;

  result = i = 0;

  if (n != 0) {
    do {
      result = str1[i] - str2[i];
      ++i;
    } while (str1[i] != '\0' && str2[i] != '\0' && result == 0 && i < n);
  }

  if (i != n && result == 0) {
    if (str1[i] != '\0') {
      result = str1[i];
    } else if (str2[i] != '\0') {
      result = -str2[i];
    }
  }

  return result;
}
