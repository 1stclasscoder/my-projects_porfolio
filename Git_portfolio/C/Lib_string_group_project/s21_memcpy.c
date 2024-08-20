#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *src_pointer = (unsigned char *)src;
  unsigned char *dest_pointer = (unsigned char *)dest;

  for (s21_size_t i = 0; i < n; i++) {
    *dest_pointer = *src_pointer;
    dest_pointer++;
    src_pointer++;
  }

  return dest;
}
