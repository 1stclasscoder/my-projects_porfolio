#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *buffer;
  static char shift;  // сдвигаем строку на длину токена

  if (str != s21_NULL) {
    buffer = str;
    shift = 0;

    // начинается ли строка с делиметора
    int stop = FAILD;
    for (s21_size_t i = 0; buffer[i] != '\0' && !stop; ++i) {
      int is_delim = FAILD;
      for (s21_size_t j = 0; delim[j] != '\0'; ++j) {
        if (buffer[i] == delim[j]) {
          is_delim = SUCCESS;
        }
      }

      if (is_delim) {
        ++shift;
      } else {
        stop = SUCCESS;
      }
    }

    s21_size_t len = s21_strlen(buffer);

    // заканчивается ли строка делиметром
    stop = FAILD;
    int end_shift = 0;
    for (int i = len - 1; i >= 0 && !stop; --i) {
      int is_delim = FAILD;
      for (s21_size_t j = 0; delim[j] != '\0'; ++j) {
        if (buffer[i] == delim[j]) {
          is_delim = SUCCESS;
        }
      }

      if (is_delim) {
        ++end_shift;
      } else {
        stop = SUCCESS;
      }
    }

    buffer[len - end_shift] = '\0';
  }

  buffer += shift;

  if (*buffer == '\0') {
    buffer = s21_NULL;
  } else {
    int found = FAILD;

    int d_count = 0;

    for (s21_size_t i = 0; buffer[i] != '\0' && !found; ++i) {
      int is_delim = FAILD;
      for (s21_size_t j = 0; delim[j] != '\0'; ++j) {
        if (buffer[i] == delim[j]) {
          is_delim = SUCCESS;
        }
      }

      if (is_delim) {
        ++d_count;
      } else if (d_count != 0) {
        found = SUCCESS;
        shift = i;
        buffer[i - d_count] = '\0';
      }
    }

    if (!found) {
      shift = s21_strlen(buffer);  // дошли до конца строки, свдигаем на '\0'
    }
  }

  return buffer;
}