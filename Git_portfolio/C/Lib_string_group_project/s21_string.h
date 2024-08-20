#pragma once

#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define FAILD 0
#define SUCCESS 1

#define s21_NULL ((void *)0)
#define MAX 1000

extern char error[MAX];

typedef long unsigned s21_size_t;

typedef struct flag_sprintf {
  int for_zero_double;
  int minus;
  int plus;
  int space;
  int sharp;
  int zero;
  int width;
  int accurancy_dot;
  int length;
  int number_system;
  int flag_size;
  int dot;
  int upper_case;
  int g;
  int e;
} flag_sprintf;

int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strtok(char *str, const char *delim);
void *s21_memset(void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
s21_size_t s21_strlen(const char *str);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
char *s21_strchr(const char *str, int c);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
void *s21_memchr(const void *str, int c, s21_size_t n);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strerror(int errnum);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strcspn(const char *str1, const char *str2);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);

int s21_sprintf(char *str, const char *format, ...);
const char *set_parser(flag_sprintf *flags, const char *format,
                       va_list *arguments);
const char *parser_spec(const char *format, flag_sprintf *flags);
const char *parser_width(const char *format, flag_sprintf *flags,
                         va_list *arguments);
const char *parser_accurancy_dot(const char *format, flag_sprintf *flags,
                                 va_list *arguments);
char *parser(char *str, char *src, const char *format, flag_sprintf *flags,
             va_list *arguments);
char *print_decimal(char *str, flag_sprintf flags, va_list arguments);
int format_to_str(flag_sprintf flags, long int number, char *str_to_number,
                  s21_size_t size_pattern);
char get_num_char(int num, int upper_case);
s21_size_t size_of_patterns(flag_sprintf *flags, long int number);
void set_flags_double(flag_sprintf *flags, const char *format);
char *print_double(char *str, flag_sprintf flags, va_list arguments);
s21_size_t size_of_double(flag_sprintf *flags, long double number);
int double_string(flag_sprintf flags, long double number, char *str_to_double,
                  s21_size_t size_double);
flag_sprintf choose_number_system(flag_sprintf flags, const char *format);
char *print_number_system(char *str, flag_sprintf *flags, const char *format,
                          va_list *arguments);
int format_to_str_unsigned(flag_sprintf flags, long int number,
                           char *str_to_number, s21_size_t size_pattern);
s21_size_t size_of_patterns_unsigned(flag_sprintf *flags, long int number);
char *print_char(char *str, flag_sprintf flags, int symbol);
char *print_s(char *str, flag_sprintf flags, va_list *arguments);
char *print_p(char *str, flag_sprintf flags, va_list *arguments);
