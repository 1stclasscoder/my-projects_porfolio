#ifndef GREP_H
#define GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5000
#define MAX2 64

typedef struct flugs_grep {
  char paterns[MAX2][MAX];
  char file_paterns[MAX2][MAX];
  char analise_file[MAX2][MAX];
  int count_paterns;
  int count_file_paterns;
  int count_analise_file;
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int s;
  int h;
  int f;
  int o;
  int trash;
} flugs_grep;

void fill_patterns(flugs_grep *flags, char *optarg);
void fill_files(flugs_grep *flags, char *optarg);
void parse_fill(char *argv[], flugs_grep *flags, int argc);
void extra_paterns(flugs_grep *flags);
void read_flags(flugs_grep *flags);
void output_i(char *stroka, int i, int *flag_pechat, flugs_grep *flags);
void output_v(char *stroka, int i, int *flag_pechat, flugs_grep *flags);
void output_o(char *stroka, int i, flugs_grep *flags, int *not_print);
void output_stroki(char *stroka, int flag_pechat, flugs_grep *flags, int g,
                   int *count_l, int count_n, int *count_c, int *not_print);
void ouput_enter(const char *stroka);
void check_output_c(flugs_grep *flags, int g, int count_c);

#endif
