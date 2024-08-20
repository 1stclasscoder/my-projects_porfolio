#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flugs_cat flags = {
      .n = 0, .b = 0, .e = 0, .s = 0, .t = 0, .v = 0, .trash = 0};
  if (argc >= 2) {
    int i = sort(argv, argc, &flags);
    if (flags.trash != 1) {
      read(argv, argc, &flags, i);
    }
  } else
    printf("Not enough arguments");
  return 0;
}

int sort(char *argv[], int argc, flugs_cat *flags) {
  int i = 0;
  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && flags->trash != 1) {
      if (argv[i][1] != '-') {
        flags_checking(i, argv, flags);
      } else {
        flags_checking_long(i, argv, flags);
      }

    } else
      break;
  }
  return i;
}

void flags_checking(int i, char *argv[], flugs_cat *flags) {
  int g = 1;
  while (argv[i][g] != '\0' && flags->trash != 1) {
    switch (argv[i][g]) {
      case 'n':
        flags->n = 1;
        break;
      case 'b':
        flags->b = 1;
        break;
      case 'E':
        flags->e = 1;
        break;
      case 'e':
        flags->e = 1;
        flags->v = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'T':
        flags->t = 1;
        break;
      case 't':
        flags->t = 1;
        flags->v = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      default:
        flags->trash = 1;
        break;
    }
    g++;
  }
  if (flags->trash == 1) {
    printf("{cat: illegal option --%c \nusage: cat [-benstuv] [file ...]}",
           argv[i][g - 1]);
  }
}

void flags_checking_long(int i, char *argv[], flugs_cat *flags) {
  if (strcmp(argv[i], "--number-nonblank") == 0 && flags->trash != 1) {
    flags->b = 1;
  } else if (strcmp(argv[i], "--number") == 0 && flags->trash != 1) {
    flags->n = 1;
  } else if (strcmp(argv[i], "--squeeze-blank") == 0 && flags->trash != 1) {
    flags->s = 1;
  } else if (strcmp(argv[i], "--") == 0 && flags->trash != 1) {
  } else {
    flags->trash = 1;
    printf("{cat: illegal option %s\nusage: cat [-benstuv] [file ...]}",
           argv[i]);
  }
}

void read(char *argv[], int argc, flugs_cat *flags, int sch) {
  for (int u = sch; u < argc; u++) {
    FILE *file;
    file = fopen(argv[u], "r");
    if (file != NULL && flags->trash != 1) {
      char stroka[MAX];
      int n = 1;
      int l = 1;
      int y = 0;
      while (fgets(stroka, sizeof(stroka), file)) {
        if (flags->s == 1) {
          y = read_s(stroka, y);
        }
        if (flags->b == 1) {
          l = read_b(stroka, l, y);
        } else if (flags->n == 1) {
          n = read_n(n, y);
        }
        if (flags->t == 1) {
          read_t(stroka);
        }
        if (flags->e == 1) {
          read_e(stroka);
        }
        if (y < 2) {
          if (flags->v == 0) {
            printf("%s", stroka);
          } else {
            read_v(stroka);
          }
        }
      }
      fclose(file);
    } else {
      printf("\nRetcat: %s: No such file or directory", argv[u]);
    }
  }
}

void read_e(char *stroka) {
  int b = 0;
  while (stroka[b] != '\n') {
    b++;
  }
  stroka[b] = '$';
  stroka[b + 1] = '\n';
  stroka[b + 2] = '\0';
}

void read_t(char *stroka) {
  int i = 0;
  int m = 0;
  char stroka2[MAX] = {0};
  while (stroka[i] != '\0') {
    if (stroka[i] != '\t') {
      stroka2[m] = stroka[i];
      i++;
      m++;
    } else {
      stroka2[m] = '^';
      m++;
      stroka2[m] = 'I';
      m++;
      i++;
    }
  }
  int flag = 0;
  for (int g = 0; g < m; g++) {
    stroka[g] = stroka2[g];
    flag = g + 1;
  }
  stroka[flag] = '\0';
}

int read_s(const char *stroka, int y) {
  if (stroka[0] == '\n') {
    y++;
  } else {
    y = 0;
  }
  return y;
}

int read_b(const char *stroka, int l, int y) {
  if (stroka[0] != '\n' && y != 2) {
    printf("%6d\t", l);
    l++;
  }
  return l;
}

int read_n(int n, int y) {
  if (y != 2) {
    printf("%6d\t", n);
    n++;
  }
  return n;
}

void read_v(char *stroka) {
  int i = 0;
  while (stroka[i] != '\0') {
    if (stroka[i] > 0 && stroka[i] < 32 && stroka[i] != '\n' &&
        stroka[i] != '\t') {
      printf("^%c", stroka[i] + 64);
    } else if (stroka[i] == 127) {
      printf("^%c", stroka[i] - 64);
    } else
      printf("%c", stroka[i]);
    i++;
  }
}
