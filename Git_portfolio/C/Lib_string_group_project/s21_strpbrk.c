#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = s21_NULL;
  char *original_str2_pointer = (char *)str2;

  while ((*str1 != '\0') && (result == s21_NULL)) {
    str2 = original_str2_pointer;

    while (*str2 != '\0') {
      if (*str1 == *str2) {
        result = (char *)str1;
        break;
      }

      str2++;
    }

    str1++;
  }

  return result;
}
