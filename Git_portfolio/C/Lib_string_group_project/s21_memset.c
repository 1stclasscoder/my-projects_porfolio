#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  for (unsigned char *cp = str; n > 0; ++cp, --n) {
    *cp = c;
  }
  return str;
}