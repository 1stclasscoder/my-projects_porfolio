#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *new_str = s21_NULL;
  if (str == s21_NULL) {
    return (void *)new_str;
  } else {
    new_str = calloc(s21_strlen(str) + 1, sizeof(char));
    int i = 0;
    while (str[i] != '\0') {
      if (str[i] >= 65 && str[i] <= 90) {
        new_str[i] = str[i] + 32;
      } else {
        new_str[i] = str[i];
      }
      i++;
    }
    new_str[i] = '\0';
  }
  return (void *)new_str;
}
