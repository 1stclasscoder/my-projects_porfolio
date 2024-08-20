#ifndef GREP_H
#define GREP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100000
typedef struct flugs_cat {
  int n;
  int b;
  int e;
  int s;
  int t;
  int v;
  int trash;
} flugs_cat;
int sort(char *argv[], int argc, flugs_cat *flags);
void flags_checking(int i, char *argv[], flugs_cat *flags);
void flags_checking_long(int i, char *argv[], flugs_cat *flags);
void read(char *argv[], int argc, flugs_cat *flags, int sch);
void read_e(char *stroka);
void read_t(char *stroka);
void read_v(char *stroka);
int read_s(const char *stroka, int y);
int read_b(const char *stroka, int l, int y);
int read_n(int n, int y);

#endif
