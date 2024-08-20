#ifndef S21_TETRIS
#define S21_TETRIS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// #include "../frontend/S21_frontend.h"

#define WIDTH 12   // ширина
#define HEIGHT 22  // высота

typedef struct tetris_struct {
  int **field;
  int **figure;
  int stop;
  int end_game;
  int over_app;
  int down;
  int score;
  int max_score;
  int level;
} components_game;

typedef struct figures {
  int **figure;
  int rows;
  int columns;
} figure_of_game;

typedef struct buf_field {
  int buf_field[HEIGHT][WIDTH];
} buf_field;

void begining_game(components_game *components);
void end_game(components_game *components, figure_of_game *figure_game,
              figure_of_game *figure_next);
void s21_remove_field(components_game *A);
void s21_create_figure(components_game *result);
void s21_create_field(components_game *result);
void create_figures(figure_of_game *figure_matrix,
                    figure_of_game *figure_matrix_next);
void s21_create_matrix(int rows, int columns, figure_of_game *result);
void change_the_field(components_game *components, figure_of_game *figure_game,
                      buf_field *buf_field, int *x, int *y, int *fall,
                      int *count_rows);
void change_function(buf_field *buf_field, figure_of_game figure_game);
void change_row(buf_field *buf_field, figure_of_game figure_game, int *x,
                int *y, int *count_rows);
void s21_remove_figure(figure_of_game *A);
void equal_fields(buf_field *buf_field, components_game *components);
void equal_fields_back(buf_field *buf_field, components_game *components);
void full_zeros(figure_of_game *result);
void key_action(components_game *components, figure_of_game *figure_game,
                int *x, int *y);
void s21_transpose(figure_of_game *A);
void zeros_buf(buf_field *buf_field);
void cline_line(components_game *components, int i);
void cline_field(components_game *components);
void full_figure(figure_of_game *figure_matrix, int num);
void change_figure(figure_of_game *figure_matrix,
                   figure_of_game *figure_matrix_next);
void check_fall(buf_field buf_field, figure_of_game figure_game,
                components_game *components, int x, int y, int *fall);
void read_max_score(components_game *components);
void load_max_score(components_game *components);
void move_left(components_game *components, figure_of_game *figure_game, int *x,
               int *y);
void move_right(components_game *components, int *x, int *y);
void change_max_score(components_game *components);
void zeros_help_function(int *fall, int *x, int *y, int *count_rows,
                         components_game *components);
void move_down(int *y);
void key_action_do(components_game *components, figure_of_game *figure_game,
                   int *x, int *y, int key);
#endif