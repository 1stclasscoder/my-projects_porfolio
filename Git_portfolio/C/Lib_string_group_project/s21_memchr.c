#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  void *t = s21_NULL;
  const char *info = (const char *)str;
  for (s21_size_t i = 0; i < n && t == s21_NULL; i++) {
    if (info[i] == c) {
      t = (void *)&info[i];
    }
  }

  return t;
}