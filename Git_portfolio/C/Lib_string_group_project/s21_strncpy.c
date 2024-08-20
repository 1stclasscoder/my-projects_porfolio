#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  int i = 0;
  while (n > 0 && src[i] != '\0') {
    dest[i] = src[i];
    i++;
    n--;
  }
  while (n > 0) {
    dest[i] = '\0';
    i++;
    n--;
  }
  return dest;
}
