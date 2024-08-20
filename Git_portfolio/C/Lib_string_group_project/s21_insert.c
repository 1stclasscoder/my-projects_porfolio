#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_src = calloc(s21_strlen(src) + s21_strlen(str) + 1, sizeof(char));

  s21_size_t i = 0;
  s21_size_t len_src = s21_strlen(src);
  while (i < len_src && i < start_index) {
    new_src[i] = src[i];
    i++;
  }
  if (i == start_index) {
    s21_size_t j = 0;
    while (str[j] != '\0') {
      new_src[i + j] = str[j];
      j++;
    }
    while (src[i] != '\0') {
      new_src[i + j] = src[i];
      i++;
    }
    new_src[i + j] = '\0';
  } else {
    free(new_src);
    new_src = s21_NULL;
  }
  return new_src;
}