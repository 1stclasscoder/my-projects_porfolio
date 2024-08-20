#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int b = 0;
  const char *s1 = (char *)str1;
  const char *s2 = (char *)str2;
  for (s21_size_t i = 0; i < n && b == 0; i++) {
    if (s1[i] != s2[i]) {
      b = (int)(s1[i] - s2[i]);
    }
  }
  return b;
}
