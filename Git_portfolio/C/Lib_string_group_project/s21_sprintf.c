#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  s21_memset(str, 0, s21_strlen(str));

  const char cpecificators[MAX] = "cdieEfgGosuxXpn%";
  char src = *str;
  va_list arguments;
  va_start(arguments, format);
  int count = 0;
  while (*format) {
    if (*format == '%') {
      format++;
      flag_sprintf flags = {0};
      flags.number_system = 10;
      format = set_parser(&flags, format, &arguments);
      while (s21_strchr(cpecificators, *format) == 0) {
        format++;
      }
      char *buffer = parser(str, &src, format, &flags, &arguments);
      count += buffer - str;
      str = buffer;
    } else {
      *str = *format;
      str++;
      count++;
    }
    format++;
  }
  va_end(arguments);

  return count;
}

const char *set_parser(flag_sprintf *flags, const char *format,
                       va_list *arguments) {
  format = parser_spec(format, flags);
  format = parser_width(format, flags, arguments);
  if (*format == '.') {
    flags->dot = 1;
    if (flags->zero == 1) {
      flags->for_zero_double = 1;
    }
    flags->zero = 0;
    format++;
    parser_accurancy_dot(format, flags, arguments);
  }
  if (*format == 'L') {
    flags->length = 'L';
    format++;
  } else if (*format == 'l') {
    flags->length = 'l';
    format++;
  }
  if (*format == 'h') {
    flags->length = 'h';
    format++;
  }
  if (flags->width < 0) {
    flags->width = -flags->width;
    flags->minus = 1;
  }
  if (flags->accurancy_dot < 0) {
    flags->accurancy_dot = -flags->accurancy_dot;
    flags->minus = 1;
  }
  return format;
}

const char *parser_spec(const char *format, flag_sprintf *flags) {
  while (format) {
    if (*format == '-')
      flags->minus = 1;
    else if (*format == '+')
      flags->plus = 1;
    else if (*format == ' ')
      flags->space = 1;
    else if (*format == '#')
      flags->sharp = 1;
    else if (*format == '0')
      flags->zero = 1;
    else
      break;
    format++;
  }
  if (flags->plus == 1) flags->space = 0;
  if (flags->minus == 1) flags->zero = 0;
  return format;
}

const char *parser_width(const char *format, flag_sprintf *flags,
                         va_list *arguments) {
  flags->width = 0;
  if (*format == '*') {
    flags->width = va_arg(*arguments, int);
    format++;
  }
  while (format) {
    if ('0' <= *format && *format <= '9') {
      flags->width *= 10;
      flags->width += (*format - '0');
    } else
      break;
    format++;
  }
  return format;
}

const char *parser_accurancy_dot(const char *format, flag_sprintf *flags,
                                 va_list *arguments) {
  flags->accurancy_dot = 0;
  if (*format == '*') {
    flags->accurancy_dot = va_arg(*arguments, int);
    format++;
  }
  while (format) {
    if ('0' <= *format && *format <= '9') {
      flags->accurancy_dot *= 10;
      flags->accurancy_dot += (*format - '0');
    } else
      break;
    format++;
  }
  return format;
}

flag_sprintf choose_number_system(flag_sprintf flags, const char *format) {
  if (*format == 'o') {
    flags.number_system = 8;
  } else if (*format == 'u') {
    flags.number_system = 10;
  } else {
    flags.number_system = 16;
    if (*format == 'X') {
      flags.upper_case = 1;
    }
  }
  return flags;
}

char *print_number_system(char *str, flag_sprintf *flags, const char *format,
                          va_list *arguments) {
  unsigned long int number = 0;
  if (*format == 'l') {
    number = (unsigned long int)va_arg(*arguments, unsigned long int);
  } else if (*format == 'h') {
    number = (unsigned short)va_arg(*arguments, unsigned int);
  } else {
    number = (unsigned int)va_arg(*arguments, unsigned int);
  }
  s21_size_t size_pattern = size_of_patterns_unsigned(flags, number);
  char str_to_number[MAX];
  int i = format_to_str_unsigned(*flags, number, str_to_number, size_pattern);
  for (int j = i; j >= 0; j--) {
    *str = str_to_number[j];
    str++;
  }
  while (i + 1 < flags->width) {
    *str = ' ';
    str++;
    i++;
  }
  return str;
}

int format_to_str_unsigned(flag_sprintf flags, long int number,
                           char *str_to_number, s21_size_t size_pattern) {
  int i = 0;
  int flag = 0;
  unsigned long int bufer_num = number;
  if (flags.sharp && flags.number_system == 8) {
    flags.flag_size = 1;
  }
  if (flags.sharp && flags.number_system == 16) {
    flags.flag_size = 2;
  }
  while (bufer_num != 0 && str_to_number && size_pattern) {
    char sym = get_num_char(bufer_num % flags.number_system, flags.upper_case);
    str_to_number[i] = sym;
    i++;
    size_pattern--;
    bufer_num /= flags.number_system;
  }
  if (flags.accurancy_dot - i > 0) {
    flags.accurancy_dot = flags.accurancy_dot - i;
    flags.zero = 1;
  } else
    flag = 1;
  if (size_pattern == 1 && flags.zero == 1 && flags.flag_size == 1)
    flags.zero = 0;
  while (flags.zero && str_to_number && (size_pattern - flags.flag_size > 0) &&
         (flags.accurancy_dot || flag)) {
    if (size_pattern == 1 && flags.flag_size == 1) {
      break;
    }
    str_to_number[i] = '0';
    i++;
    size_pattern--;
    flags.accurancy_dot--;
  }
  if (flags.sharp && flags.number_system == 8) {
    str_to_number[i] = '0';
    i++;
    size_pattern--;
  } else if (flags.sharp && flags.number_system == 16 && flags.upper_case) {
    str_to_number[i] = 'X';
    i++;
    size_pattern--;
    str_to_number[i] = '0';
    i++;
    size_pattern--;
  } else if (flags.sharp && flags.number_system == 16 && !flags.upper_case) {
    str_to_number[i] = 'x';
    i++;
    size_pattern--;
    str_to_number[i] = '0';
    i++;
    size_pattern--;
  }
  if (size_pattern != 0 && flags.minus == 0) {
    while ((size_pattern > 0) && str_to_number) {
      str_to_number[i] = ' ';
      i++;
      size_pattern--;
    }
  }
  return i - 1;
}

s21_size_t size_of_patterns_unsigned(flag_sprintf *flags, long int number) {
  s21_size_t count = 0;
  long int bufer_num = number;
  if (bufer_num < 0) bufer_num = -bufer_num;
  while (bufer_num != 0) {
    bufer_num = bufer_num / flags->number_system;
    count++;
  }
  if (count == 0 &&
      (flags->accurancy_dot == 0 || flags->width == 0 || flags->space == 0)) {
    count++;
  }
  if (flags->number_system == 8 && flags->sharp) {
    count++;
  }
  if ((s21_size_t)flags->accurancy_dot > count)
    count = (s21_size_t)flags->accurancy_dot;
  if (number < 0 || flags->space == 1 || flags->plus == 1) {
    flags->flag_size = 1;
    count++;
  }
  if (flags->number_system == 16 && flags->sharp) {
    count += 2;
  }
  if ((s21_size_t)flags->width > count) {
    count = (s21_size_t)flags->width;
  }
  if (count == 0 && flags->accurancy_dot == 0 && flags->plus == 0 &&
      flags->space == 0 && flags->dot == 0) {
    count++;
  }
  return count;
}

char *print_char(char *str, flag_sprintf flags, int symbol) {
  char *pointer = s21_NULL;
  while (flags.width - 1 > 0 && !flags.minus) {
    *str = ' ';
    str++;
    flags.width--;
  }
  if (symbol <= 127) {
    *str = symbol;
    str++;
    while (flags.width - 1 > 0 && flags.minus) {
      *str = ' ';
      str++;
      flags.width--;
    }
    pointer = str;
  }
  return pointer;
}

char *parser(char *str, char *src, const char *format, flag_sprintf *flags,
             va_list *arguments) {
  if (*format == 'd' || *format == 'i') {
    str = print_decimal(str, *flags, *arguments);  // ГЕРМАН
  } else if (*format == 'u' || *format == 'o' || *format == 'x' ||
             *format == 'X') {  // СЕМЕН
    *flags = choose_number_system(*flags, format);
    str = print_number_system(str, flags, (format - 1), arguments);
  } else if (*format == 'c') {  // СЕМЕН
    int symbol = va_arg(*arguments, int);
    str = print_char(str, *flags, symbol);
  } else if (*format == 's') {  // РОМА
    str = print_s(str, *flags, arguments);
  } else if (*format == 'p') {  // РОМА
    str = print_p(str, *flags, arguments);
  } else if (*format == 'f' || *format == 'F') {
    set_flags_double(flags, format);
    str = print_double(str, *flags, *arguments);
  } else if (*format == 'e' || *format == 'E' || *format == 'g' ||
             *format == 'G') {  // АНДРЕЙ
  } else if (*format == '%') {  // СЕМЕН
    str = print_char(str, *flags, '%');
  } else {  // РОМА
    str = s21_NULL;
  }
  if (str == 0) *src = '\0';
  return str;
}

char *print_s(char *str, flag_sprintf flags, va_list *arguments) {
  char *ptr = str;
  char *string = va_arg(*arguments, char *);
  if (string) {
    int temp = flags.width;
    if ((s21_size_t)flags.width < (s21_size_t)s21_strlen(string))
      flags.width = s21_strlen(string);
    int blank = flags.width - s21_strlen(string);
    if (flags.accurancy_dot == 0) flags.accurancy_dot = flags.width;
    if (flags.accurancy_dot != 0 && flags.accurancy_dot < temp)
      blank = temp - flags.accurancy_dot;
    while (blank && !flags.minus) {
      *str = ' ';
      str++;
      blank--;
    }
    while (*string != '\0') {
      if (!flags.accurancy_dot) break;
      *str = *string;
      str++;
      string++;
      flags.accurancy_dot--;
    }
    while (blank && flags.minus) {
      *str = ' ';
      str++;
      blank--;
    }
  } else {
    str = s21_memcpy(str, "(null)", 6);
    str += 6;
  }
  if (ptr) ptr = str;
  return ptr;
}

char *print_p(char *str, flag_sprintf flags, va_list *arguments) {
  unsigned long int ptr =
      (unsigned long int)va_arg(*arguments, unsigned long int);
  flags.number_system = 16;
  flags.sharp = 1;
  flags.upper_case = 0;
  s21_size_t size_to_num = size_of_patterns_unsigned(&flags, ptr);
  char buffer[MAX];
  int i = format_to_str_unsigned(flags, ptr, buffer, size_to_num);
  for (int j = i; j >= 0; j--) {
    *str = buffer[j];
    str++;
  }
  while (i + 1 < flags.width) {
    *str = ' ';
    str++;
    i++;
  }
  return str;
}

char *print_decimal(char *str, flag_sprintf flags, va_list arguments) {
  long int number = 0;
  if (flags.length == 'l') {
    number = (long int)va_arg(arguments, long int);
  } else if (flags.length == 'h') {
    number = (short)va_arg(arguments, int);
  } else {
    number = (int)va_arg(arguments, int);
  }
  if (!(number == 0 && flags.dot == 1 && flags.accurancy_dot == 0)) {
    s21_size_t size_pattern = size_of_patterns(&flags, number);
    char str_to_number[MAX];
    int i = format_to_str(flags, number, str_to_number, size_pattern);
    for (int j = i; j >= 0; j--) {
      *str = str_to_number[j];
      str++;
    }
    while (i + 1 < flags.width) {
      *str = ' ';
      str++;
      i++;
    }
  }
  return str;
}

int format_to_str(flag_sprintf flags, long int number, char *str_to_number,
                  s21_size_t size_pattern) {
  int flag = 0;
  if (number < 0) {
    flag = 1;
    number = -number;
  }
  int i = 0;
  long int bufer_num = number;
  if (bufer_num == 0) {
    char sym = '0';
    str_to_number[i] = sym;
    i++;
    size_pattern--;
  }
  while (bufer_num != 0 && str_to_number && size_pattern) {
    char sym = get_num_char(bufer_num % flags.number_system, flags.upper_case);
    str_to_number[i] = sym;
    i++;
    size_pattern--;
    bufer_num /= 10;
  }

  if (flag == 1) number = -number;

  if (flags.accurancy_dot - i > 0) {
    flags.accurancy_dot = flags.accurancy_dot - i;
    flags.zero = 1;
  } else
    flag = 1;

  if (size_pattern == 1 && flags.zero == 1 && flags.flag_size == 1)
    flags.zero = 0;
  while (flags.zero && str_to_number && (size_pattern - flags.flag_size > 0) &&
         (flags.accurancy_dot || flag)) {
    if (size_pattern == 1 && flags.flag_size == 1) {
      break;
    }
    str_to_number[i] = '0';
    i++;
    size_pattern--;
    flags.accurancy_dot--;
  }
  if (flags.space == 1 && number > 0 && size_pattern != 0) {
    str_to_number[i] = ' ';
    i++;
    size_pattern--;
  }
  if (number < 0 && size_pattern != 0) {
    str_to_number[i] = '-';
    i++;
    size_pattern--;
  }

  if (number > 0 && flags.plus == 1 && size_pattern != 0) {
    str_to_number[i] = '+';
    i++;
    size_pattern--;
  }
  if (size_pattern != 0 && flags.minus == 0) {
    while ((size_pattern > 0) && str_to_number) {
      str_to_number[i] = ' ';
      i++;
      size_pattern--;
    }
  }

  return i - 1;
}

char get_num_char(int num, int upper_case) {
  char flag = '0';
  switch (num) {
    case 10:
      flag = (char)('a' - upper_case * 32);
      break;
    case 11:
      flag = (char)('b' - upper_case * 32);
      break;
    case 12:
      flag = (char)('c' - upper_case * 32);
      break;
    case 13:
      flag = (char)('d' - upper_case * 32);
      break;
    case 14:
      flag = (char)('e' - upper_case * 32);
      break;
    case 15:
      flag = (char)('f' - upper_case * 32);
      break;
  }
  if (num <= 9 && num >= 0) {
    flag = (char)(num + 48);
  }
  return flag;
}

s21_size_t size_of_patterns(flag_sprintf *flags, long int number) {
  s21_size_t count = 0;
  long int bufer_num = number;
  if (bufer_num < 0) bufer_num = -bufer_num;
  while (bufer_num != 0) {
    bufer_num = bufer_num / 10;
    count++;
  }
  if (count == 0 &&
      (flags->accurancy_dot == 0 || flags->width == 0 || flags->space == 0)) {
    count++;
  }
  if ((s21_size_t)flags->accurancy_dot > count)
    count = (s21_size_t)flags->accurancy_dot;
  if (number < 0 || flags->space == 1 || flags->plus == 1) {
    flags->flag_size = 1;
    count++;
  }
  if ((s21_size_t)flags->width > count) {
    count = (s21_size_t)flags->width;
  }
  if (count == 0 && flags->accurancy_dot == 0 && flags->plus == 0 &&
      flags->space == 0 && flags->dot == 0) {
    count++;
  }
  return count;
}

char *print_double(char *str, flag_sprintf flags, va_list arguments) {
  long double number = 0;
  if (flags.length == 'L')
    number = va_arg(arguments, long double);
  else
    number = va_arg(arguments, double);
  if (flags.accurancy_dot <= 5 && flags.dot == 0) flags.accurancy_dot = 6;
  s21_size_t size_double = size_of_double(&flags, number);
  char str_to_double[MAX];
  int i = double_string(flags, number, str_to_double, size_double);
  for (int j = i; j >= 0; j--) {
    *str = str_to_double[j];
    //            printf ("%c\n", str_to_double[j]);
    str++;
  }
  while (i + 1 < flags.width) {
    *str = ' ';
    str++;
    i++;
  }
  return str;
}

s21_size_t size_of_double(flag_sprintf *flags, long double number) {
  s21_size_t count2 = 0;
  s21_size_t count = 0;
  long double bufer_num = number;
  if (bufer_num < 0) bufer_num = -bufer_num;
  long int int_bufer = bufer_num;
  if (int_bufer == 0) count2++;
  while (int_bufer != 0) {
    int_bufer = int_bufer / 10;
    count2++;
  }
  count = (s21_size_t)flags->accurancy_dot + count2;
  if (flags->accurancy_dot != 0) count++;  // Под точку
  if (number < 0 || flags->space == 1 || flags->plus == 1) {
    flags->flag_size = 1;
    count++;
  }

  if ((s21_size_t)flags->width > count) {
    count = (s21_size_t)flags->width;
  }
  return count;
}

void set_flags_double(flag_sprintf *flags, const char *format) {
  if (*format == 'F') flags->upper_case = 1;
  // ДОПОЛНИТЬ С УЧЕТОМ БОНУСНОЙ ЧАСТИ
}

int double_string(flag_sprintf flags, long double number, char *str_to_double,
                  s21_size_t size_double) {
  if (flags.for_zero_double == 1) {
    flags.zero = 1;
  }

  int i = 0;
  // is_nan_or_inf (str_to_number, number, flags); // ДОПИСАТЬ Сучетом бонусной
  // части!!!!!
  int flag = 0;
  if (number < 0) {
    number = -number;
    flag = 1;
  }
  long double integer = 0;
  long double frac = modfl(number, &integer);
  int accurancy = flags.accurancy_dot;
  if (frac + 0.000000000000001 >= 1) {
    frac = 0;
    integer++;
  }
  if (accurancy == 0 && frac * 10 > 4) integer += 1;
  int count_for_zero = 0;
  int flag_forzero2 = 0;
  for (int k = 0; k < 15; k++) {
    frac *= 10;
    accurancy--;
    if ((int)frac != 0 || accurancy <= 0) {
      flag_forzero2 = 1;
      break;
    }
    count_for_zero++;
  }

  if (accurancy == 0) {
    if (fmodl(fabsl(frac) * 10, 10.0) > 4) frac = round(frac);
  }

  while (accurancy > 0) {
    frac *= 10;
    accurancy--;
  }
  if (fmodl(fabsl(frac) * 10, 10.0) > 4) frac = round(frac);

  long int int_integer = integer;

  if (flags.accurancy_dot != 0) {
    long int copy_frac = frac;
    long int int_frac = frac;
    if (int_frac == 0) {
      while (count_for_zero) {
        char sym1 = '0';
        str_to_double[i] = sym1;
        i++;
        size_double--;
        count_for_zero--;
      }
      str_to_double[i] = '0';
      i++;
      size_double--;
    }
    while (int_frac != 0 && str_to_double && size_double) {
      char sym2 =
          get_num_char(int_frac % flags.number_system, flags.upper_case);
      str_to_double[i] = sym2;
      i++;
      size_double--;
      int_frac /= 10;
    }
    while (count_for_zero && size_double && str_to_double && flag_forzero2 &&
           copy_frac != 0) {
      str_to_double[i] = '0';
      i++;
      size_double--;
      count_for_zero--;
    }
    if (str_to_double) {
      str_to_double[i] = '.';
      i++;
      size_double--;
    }
  }
  if (int_integer == 0) {
    char sym3 = '0';
    str_to_double[i] = sym3;
    i++;
    size_double--;
  }

  while (int_integer != 0 && str_to_double && size_double) {
    char sym4 =
        get_num_char(int_integer % flags.number_system, flags.upper_case);
    str_to_double[i] = sym4;
    i++;
    size_double--;
    int_integer /= 10;
  }
  //    printf ("%s\n", str_to_double);
  if (flag == 1) number = -number;
  if (flags.accurancy_dot - i > 0) {
    flags.accurancy_dot = flags.accurancy_dot - i;
    flags.zero = 1;
  }
  if (size_double == 1 && flags.zero == 1 && flags.flag_size == 1)
    flags.zero = 0;
  while (flags.zero && str_to_double && (size_double - flags.flag_size > 0)) {
    if (size_double == 1 && flags.flag_size == 1) {
      break;
    }
    str_to_double[i] = '0';
    i++;
    size_double--;
    flags.accurancy_dot--;
  }
  if (flags.space == 1 && number > 0 && size_double != 0) {
    str_to_double[i] = ' ';
    i++;
    size_double--;
  }
  if (number < 0 && size_double != 0) {
    str_to_double[i] = '-';
    i++;
    size_double--;
  }
  if (number > 0 && flags.plus == 1 && size_double != 0) {
    str_to_double[i] = '+';
    i++;
    size_double--;
  }
  if (size_double != 0 && flags.minus == 0) {
    while ((size_double > 0) && str_to_double) {
      str_to_double[i] = ' ';
      i++;
      size_double--;
    }
    //        printf ("%s\n", str_to_double);
  }
  //        printf ("%s\n", str_to_double);
  return i - 1;
}