#include "s21_grep.h"

int main(int argc, char *argv[]) {
  flugs_grep flags = {0};
  if (argc < 3) {
    printf("grep: not enough arguments\n");
  } else if (argc <= MAX2 && flags.trash != 1) {
    parse_fill(argv, &flags, argc);
    read_flags(&flags);
  } else if (flags.trash) {
  } else if (argc > MAX2)
    printf("grep: too many arguments\n");
  return 0;
}

void parse_fill(char *argv[], flugs_grep *flags, int argc) {
  int option;
  while ((option = getopt(argc, argv, "e:ivclnhsf:o")) != -1 &&
         flags->trash != 1) {
    switch (option) {
      case 'e':
        flags->e = 1;
        fill_patterns(flags, optarg);
        break;
      case 'f':
        flags->f = 1;
        fill_files(flags, optarg);
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'o':
        flags->o = 1;
        break;
      default:
        flags->trash = 1;
        printf(
            "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
            "[-C[num]]\n\t[-e pattern] [-f file] [--binary-files=value] "
            "[--color=when]\n\t[--context[=num]] [--directories=action] "
            "[--label] [--line-buffered]\n\t[--null] [pattern] [file ...]\n");
        break;
    }
  }
  if (flags->trash != 1) {
    for (int i = optind; i < argc; i++) {
      if ((strlen(argv[i])) > MAX) {
        printf("grep: argument is too long\n");
      } else {
        if (flags->count_paterns == 0 && flags->count_file_paterns == 0) {
          strcpy(flags->paterns[flags->count_paterns], argv[i]);
          flags->count_paterns++;
        } else {
          strcpy(flags->analise_file[flags->count_analise_file], argv[i]);
          flags->count_analise_file++;
        }
      }
    }
    if (flags->f == 1) extra_paterns(flags);
  }
}

void extra_paterns(flugs_grep *flags) {
  int b = 0;
  for (int i = 0; i < flags->count_file_paterns; i++) {
    FILE *file;
    file = fopen(flags->file_paterns[i], "r");
    if (file != NULL) {
      char stroka2[MAX];
      while (fgets(stroka2, sizeof(stroka2), file)) {
        int length = strlen(stroka2);
        if (stroka2[length - 1] == '\n') stroka2[length - 1] = '\0';
        strcpy(flags->paterns[flags->count_paterns], stroka2);
        flags->count_paterns++;
        b++;
      }
      fclose(file);
    } else if (flags->s != 1)
      printf("grep: %s: No such file or directory\n", flags->file_paterns[b]);
  }
}

void fill_patterns(flugs_grep *flags, char *optarg) {
  strcpy(flags->paterns[flags->count_paterns], optarg);
  flags->count_paterns++;
}
void fill_files(flugs_grep *flags, char *optarg) {
  strcpy(flags->file_paterns[flags->count_file_paterns], optarg);
  flags->count_file_paterns++;
}

void read_flags(flugs_grep *flags) {
  for (int g = 0; g < flags->count_analise_file; g++) {
    FILE *file;
    int count_c = 0;
    file = fopen(flags->analise_file[g], "r");
    if (file != NULL) {
      int count_n = 1;
      char stroka[MAX];
      int count_l = 0;
      while (fgets(stroka, sizeof(stroka), file)) {
        int flag_pechat = 0;
        int not_print = 0;
        for (int i = 0; i < flags->count_paterns; i++) {
          if (flags->v != 1 && flags->o != 1) {
            if (flags->i != 1) {
              if (strstr(stroka, flags->paterns[i]) != NULL) flag_pechat = 1;
            }
            if (flags->i == 1) output_i(stroka, i, &flag_pechat, flags);
            output_stroki(stroka, flag_pechat, flags, g, &count_l, count_n,
                          &count_c, &not_print);
          } else if (flags->v == 1 || flags->i == 1) {
            if (flags->i == 1) {
              output_i(stroka, i, &flag_pechat, flags);
            } else if (flags->v == 1) {
              output_v(stroka, i, &flag_pechat, flags);
            }
            output_stroki(stroka, flag_pechat, flags, g, &count_l, count_n,
                          &count_c, &not_print);
          } else {
            if (flags->o == 1) {
              output_o(stroka, i, flags, &not_print);
            }
          }
          count_n++;
        }
      }
      fclose(file);
    } else if (flags->s != 1) {
      printf("grep: %s: No such file or directory\n", flags->analise_file[g]);
    }
    check_output_c(flags, g, count_c);
  }
}

void output_i(char *stroka, int i, int *flag_pechat, flugs_grep *flags) {
  regex_t regex;
  regcomp(&regex, flags->paterns[i], REG_ICASE);
  if (flags->v == 0) {
    if (regexec(&regex, stroka, 0, NULL, 0) == 0) *flag_pechat = 1;
  } else {
    if (regexec(&regex, stroka, 0, NULL, 0) != 0) {
      *flag_pechat = 1;
    }
  }
  regfree(&regex);
}

void output_v(char *stroka, int i, int *flag_pechat, flugs_grep *flags) {
  regex_t regex;
  regcomp(&regex, flags->paterns[i], REG_EXTENDED);
  if (regexec(&regex, stroka, 0, NULL, 0) != 0) {
    *flag_pechat = 1;
  }
  regfree(&regex);
}

void output_o(char *stroka, int i, flugs_grep *flags, int *not_print) {
  if (strstr(stroka, flags->paterns[i]) != NULL && *not_print != 1) {
    printf("%s", flags->paterns[i]);
    *not_print = 1;
  }
}

void output_stroki(char *stroka, int flag_pechat, flugs_grep *flags, int g,
                   int *count_l, int count_n, int *count_c, int *not_print) {
  if (flags->l == 1 && flags->c != 1) {
    if (flag_pechat == 1 && *count_l != 1) {
      printf("%s\n", flags->analise_file[g]);
      *count_l = 1;
    }
  } else if (flags->n == 0 && flags->c != 1) {
    if (((flags->count_analise_file == 1 || flags->h == 1) &&
         flag_pechat == 1) &&
        *not_print != 1) {
      printf("%s", stroka);
      *not_print = 1;
      ouput_enter(stroka);
    } else if ((flags->count_analise_file > 1 && flag_pechat == 1 &&
                flags->h == 0) &&
               *not_print != 1) {
      printf("%s:%s", flags->analise_file[g], stroka);
      *not_print = 1;
      ouput_enter(stroka);
    }
  } else if (flags->n == 1 && flags->c != 1) {
    if (((flags->count_analise_file == 1 || flags->h == 1) &&
         flag_pechat == 1) &&
        *not_print != 1) {
      printf("%d:%s", count_n, stroka);
      *not_print = 1;
      ouput_enter(stroka);
    } else if ((flags->count_analise_file > 1 && flag_pechat == 1 &&
                flags->h == 0) &&
               *not_print != 1) {
      printf("%s:%d:%s", flags->analise_file[g], count_n, stroka);
      *not_print = 1;
      ouput_enter(stroka);
    }
  }
  if (flag_pechat == 1) {
    *count_c = *count_c + 1;
  }
}

void ouput_enter(const char *stroka) {
  int b = 0;
  while (stroka[b] != '\0') {
    b++;
  }
  if (stroka[b - 1] != '\n') printf("\n");
}

void check_output_c(flugs_grep *flags, int g, int count_c) {
  if (flags->l == 0) {
    if (flags->c == 1 && flags->count_analise_file == 1)
      printf("%d\n", count_c);
    else if (flags->count_analise_file > 1 && flags->c == 1)
      printf("%s:%d\n", flags->analise_file[g], count_c);
  } else if (flags->l == 1) {
    if (flags->c == 1 && flags->count_analise_file == 1 && count_c == 0)
      printf("0\n");
    else if (flags->c == 1 && flags->count_analise_file == 1 && count_c > 0)
      printf("1\n%s\n", flags->analise_file[g]);
    else if (flags->count_analise_file > 1 && flags->c == 1 && count_c == 0)
      printf("%s:0\n", flags->analise_file[g]);
    else if (flags->count_analise_file > 1 && flags->c == 1 && count_c > 0)
      printf("%s:1\n%s\n", flags->analise_file[g], flags->analise_file[g]);
  }
}
