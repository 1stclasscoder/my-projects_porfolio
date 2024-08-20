#include "./S21_backend.h"

#include "../../gui/cli/S21_frontend.h"

void begining_game(components_game *components) {
  s21_create_field(components);
  components->stop = 0;
  components->end_game = 0;
  components->over_app = 0;
  components->score = 0;
  components->level = 0;
  read_max_score(components);
}

void change_max_score(components_game *components) {
  if (components->score > components->max_score) {
    components->max_score = components->score;
    load_max_score(components);
  }
}

void change_the_field(components_game *components, figure_of_game *figure_game,
                      buf_field *buf_field, int *x, int *y, int *fall,
                      int *count_rows) {
  equal_fields(buf_field, components);
  *count_rows = 0;
  while (*count_rows < figure_game->rows) {
    change_row(buf_field, *figure_game, x, y, count_rows);
  }
  check_fall(*buf_field, *figure_game, components, *x, *y, fall);
}

void check_fall(buf_field buf_field, figure_of_game figure_game,
                components_game *components, int x, int y, int *fall) {
  for (int j = 0; j < figure_game.columns; j++) {
    if (buf_field.buf_field[y][x - j] != 0 &&
        buf_field.buf_field[y + 1][x - j] != 0) {
      if (buf_field.buf_field[y - 1][x - j] == 0 &&
          (buf_field.buf_field[y - 2][x - j] == 4 ||
           buf_field.buf_field[y - 2][x - j] == 5)) {
      } else {
        *fall = 1;
        break;
      }
    }
  }
  if (*fall == 1 && y == 0) {
    components->end_game = 1;
  }
}

void key_action(components_game *components, figure_of_game *figure_game,
                int *x, int *y) {
  int key = getch();
  key_action_do(components, figure_game, x, y, key);
}

void key_action_do(components_game *components, figure_of_game *figure_game,
                   int *x, int *y, int key) {
  components->stop = 0;
  switch (key) {
    case KEY_UP:
      s21_transpose(figure_game);
      if (figure_game->columns > *x) {
        *x = figure_game->columns;
      }
      break;
    case KEY_LEFT:
      move_left(components, figure_game, x, y);
      break;
    case KEY_RIGHT:
      move_right(components, x, y);
      break;
    case 32:
      components->stop = 1;
      break;
    case 113:
      components->end_game = 1;
      components->over_app = 1;
      break;
    case KEY_DOWN:
      components->down = 1;
      break;
  }
}

void move_left(components_game *components, figure_of_game *figure_game, int *x,
               int *y) {
  if (components->field[*y][*x - figure_game->columns] == 0) {
    *x = *x - 1;
  }
}
void move_right(components_game *components, int *x, int *y) {
  if (components->field[*y][*x + 1] == 0) {
    *x = *x + 1;
  }
}

void change_row(buf_field *buf_field, figure_of_game figure_game, int *x,
                int *y, int *count_rows) {
  for (int i = 0; i < figure_game.columns; i++) {
    if (figure_game.figure[figure_game.rows - *count_rows - 1]
                          [figure_game.columns - i - 1] != 0) {
      buf_field->buf_field[*y - *count_rows][*x - i] =
          figure_game.figure[figure_game.rows - *count_rows - 1]
                            [figure_game.columns - i - 1];
    }
  }
  *count_rows = *count_rows + 1;
}

void s21_create_field(components_game *result) {
  (*result).field = calloc(HEIGHT, sizeof(int *));
  for (int i = 0; i < HEIGHT; i++) {
    result->field[i] = (int *)calloc(WIDTH, sizeof(int));
  }
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (j == 0 || j == WIDTH - 1)
        result->field[i][j] = 1;
      else if (i == HEIGHT - 1)
        result->field[i][j] = 2;
      else
        result->field[i][j] = 0;
    }
  }
}

void create_figures(figure_of_game *figure_matrix,
                    figure_of_game *figure_matrix_next) {
  int num_figure;
  int num_figure2;
  srand(time(NULL));
  num_figure = rand() % 7;
  num_figure2 = rand() % 7;
  if (figure_matrix->columns == 0) {
    full_figure(figure_matrix, num_figure);
  } else {
    change_figure(figure_matrix, figure_matrix_next);
  }
  s21_remove_figure(figure_matrix_next);
  full_figure(figure_matrix_next, num_figure2);
}

void change_figure(figure_of_game *figure_matrix,
                   figure_of_game *figure_matrix_next) {
  s21_remove_figure(figure_matrix);
  s21_create_matrix(figure_matrix_next->rows, figure_matrix_next->columns,
                    figure_matrix);
  for (int i = 0; i < figure_matrix_next->rows; i++) {
    for (int j = 0; j < figure_matrix_next->columns; j++) {
      figure_matrix->figure[i][j] = figure_matrix_next->figure[i][j];
    }
  }
  s21_remove_figure(figure_matrix_next);
}

void full_figure(figure_of_game *figure_matrix, int num) {
  switch (num) {
    case 0:
      s21_create_matrix(1, 4, figure_matrix);
      full_zeros(figure_matrix);
      figure_matrix->figure[0][0] = 3;
      figure_matrix->figure[0][1] = 3;
      figure_matrix->figure[0][2] = 3;
      figure_matrix->figure[0][3] = 3;
      break;
    case 1:
      s21_create_matrix(2, 3, figure_matrix);
      full_zeros(figure_matrix);
      figure_matrix->figure[0][0] = 4;
      figure_matrix->figure[1][0] = 4;
      figure_matrix->figure[1][1] = 4;
      figure_matrix->figure[1][2] = 4;
      break;
    case 2:
      s21_create_matrix(2, 3, figure_matrix);
      full_zeros(figure_matrix);
      figure_matrix->figure[1][0] = 5;
      figure_matrix->figure[1][1] = 5;
      figure_matrix->figure[1][2] = 5;
      figure_matrix->figure[0][2] = 5;
      break;
    case 3:
      s21_create_matrix(2, 2, figure_matrix);
      full_zeros(figure_matrix);
      figure_matrix->figure[0][0] = 6;
      figure_matrix->figure[1][0] = 6;
      figure_matrix->figure[0][1] = 6;
      figure_matrix->figure[1][1] = 6;
      break;
    case 4:
      s21_create_matrix(2, 3, figure_matrix);
      full_zeros(figure_matrix);
      figure_matrix->figure[1][0] = 7;
      figure_matrix->figure[1][1] = 7;
      figure_matrix->figure[0][1] = 7;
      figure_matrix->figure[0][2] = 7;
      break;
    case 5:
      s21_create_matrix(2, 3, figure_matrix);
      full_zeros(figure_matrix);
      figure_matrix->figure[0][0] = 8;
      figure_matrix->figure[0][1] = 8;
      figure_matrix->figure[1][1] = 8;
      figure_matrix->figure[1][2] = 8;
      break;
    case 6:
      s21_create_matrix(2, 3, figure_matrix);
      full_zeros(figure_matrix);
      figure_matrix->figure[1][0] = 9;
      figure_matrix->figure[1][1] = 9;
      figure_matrix->figure[1][2] = 9;
      figure_matrix->figure[0][1] = 9;
      break;
  }
}

void s21_create_matrix(int rows, int columns, figure_of_game *result) {
  (*result).rows = rows;
  (*result).columns = columns;
  (*result).figure = (int **)calloc(rows, sizeof(int *));
  for (int i = 0; i < rows; i++) {
    result->figure[i] = (int *)calloc(columns, sizeof(int));
  }
}

void s21_remove_field(components_game *A) {
  if ((*A).field != NULL) {
    for (int j = 0; j < HEIGHT; ++j) {
      free((*A).field[j]);
    }
  }
  free((*A).field);
  (*A).field = NULL;
}

void s21_remove_figure(figure_of_game *A) {
  if ((*A).figure != NULL) {
    for (int j = 0; j < (*A).rows; ++j) {
      free((*A).figure[j]);
    }
  }
  free((*A).figure);
  (*A).figure = NULL;
  (*A).columns = 0;
  (*A).rows = 0;
}

void end_game(components_game *components, figure_of_game *figure_game,
              figure_of_game *figure_next) {
  s21_remove_field(components);
  s21_remove_figure(figure_game);
  s21_remove_figure(figure_next);
}

void equal_fields(buf_field *buf_field, components_game *components) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      buf_field->buf_field[i][j] = components->field[i][j];
    }
  }
}

void equal_fields_back(buf_field *buf_field, components_game *components) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      components->field[i][j] = buf_field->buf_field[i][j];
    }
  }
}
void full_zeros(figure_of_game *result) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->figure[i][j] = 0;
    }
  }
}

void s21_transpose(figure_of_game *A) {
  figure_of_game result = {0};
  s21_create_matrix(A->columns, A->rows, &result);
  int k = (*A).rows - 1;
  for (int i = 0; i < (*A).rows; ++i) {
    for (int j = 0; j < (*A).columns; ++j) {
      result.figure[j][k] = (*A).figure[i][j];
    }
    k--;
  }
  s21_remove_figure(A);
  s21_create_matrix(result.rows, result.columns, A);
  for (int i = 0; i < result.rows; ++i) {
    for (int j = 0; j < result.columns; ++j) {
      (*A).figure[i][j] = result.figure[i][j];
    }
  }
}

void cline_field(components_game *components) {
  int check_line = 0;
  int count = 0;
  for (int i = 0; i < HEIGHT - 1; i++) {
    check_line = 0;
    for (int j = 1; j < WIDTH - 1; j++) {
      if (components->field[i][j] == 0) {
        check_line = 1;
      }
    }
    if (check_line == 0) {
      cline_line(components, i);
      count++;
    }
  }
  if (count == 1) {
    components->score += 100;
  } else if (count == 2) {
    components->score += 300;
  } else if (count == 3) {
    components->score += 700;
  } else if (count == 4) {
    components->score += 1500;
  }
  components->level = components->score / 600;
  if (components->level > 9) components->level = 9;
}

void cline_line(components_game *components, int i) {
  buf_field buf_field = {0};
  zeros_buf(&buf_field);
  int k = HEIGHT - 2;
  for (int a = HEIGHT - 2; a >= 0; a--) {
    for (int j = 0; j < WIDTH; j++) {
      if (a != i) {
        buf_field.buf_field[k][j] = components->field[a][j];
      }
    }
    if (a != i) {
      k--;
    }
  }
  equal_fields_back(&buf_field, components);
}

void zeros_buf(buf_field *buf_field) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (j == 0 || j == WIDTH - 1)
        buf_field->buf_field[i][j] = 1;
      else if (i == HEIGHT - 1)
        buf_field->buf_field[i][j] = 2;
      else
        buf_field->buf_field[i][j] = 0;
    }
  }
}

void read_max_score(components_game *components) {
  FILE *file = fopen("./max_score.txt", "r");  // Открытие файла для записи
  if (file) {
    fscanf(file, "%d", &components->max_score);  // Чтение числа из файла
    fclose(file);                                // Закрытие файла
  }
}

void load_max_score(components_game *components) {
  FILE *file = fopen("./max_score.txt", "w");  // Открытие файла для записи
  if (file) {
    fprintf(file, "%d", components->score);  // Запись числа в файл
    fclose(file);
  }
}

void zeros_help_function(int *fall, int *x, int *y, int *count_rows,
                         components_game *components) {
  *fall = 0;
  *x = WIDTH / 2;
  *y = 0;
  *count_rows = 0;
  components->down = 0;
}

void move_down(int *y) { *y = *y + 1; }