#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *pointer = s21_NULL;
  int needlen = s21_strlen(needle) - 1;
  char *buff = (char *)haystack;
  for (int i = 0; buff[i] != '\0' && pointer == s21_NULL; i++) {
    int flag = 1;
    int j = 0;
    while ((j <= needlen) && flag) {
      flag = buff[i + j] == needle[j];
      j++;
    }

    if (flag && (j >= needlen)) {
      pointer = &(buff[i]);
    }
  }
  return pointer;
}