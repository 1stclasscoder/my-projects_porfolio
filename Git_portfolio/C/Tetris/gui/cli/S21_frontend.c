#include "./S21_frontend.h"

void turn_on_all_ncurses() {
  initscr();
  noecho();
  cbreak();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_RED);
  init_pair(4, COLOR_GREEN, COLOR_GREEN);
  init_pair(5, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(6, COLOR_BLUE, COLOR_BLUE);
  init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(8, COLOR_CYAN, COLOR_CYAN);
  init_pair(9, COLOR_WHITE, COLOR_WHITE);
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);
}

void output_game_figures(buf_field buf_field, components_game result,
                         figure_of_game figure_next) {
  int sdv = 7;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (buf_field.buf_field[i][j] == 0)
        printw("  ");
      else if (buf_field.buf_field[i][j] == 1)
        printw("|");
      else if (buf_field.buf_field[i][j] == 2)
        printw("--");
      else {
        attron(COLOR_PAIR(buf_field.buf_field[i][j]));
        printw("  ");
        attroff(COLOR_PAIR(buf_field.buf_field[i][j]));
      }
      if (i == 0 && j == WIDTH - 1) {
        printw("   MAX SCORE - %d", result.max_score);
      }
      if (i == 2 && j == WIDTH - 1) {
        printw("   SCORE - %d", result.score);
      }
      if (i == 4 && j == WIDTH - 1) {
        printw("   LEVEL - %d", result.level);
      }
      if (i == 6 && j == WIDTH - 1) {
        printw("   NEXT FIGURE:");
      }
      for (int k = sdv; k < figure_next.rows + sdv; k++) {
        if (i == k && j == WIDTH - 1) {
          printw("   ");
          for (int l = 0; l < figure_next.columns; l++) {
            if (figure_next.figure[k - sdv][l] == 0) {
              printw("  ");
            } else {
              attron(COLOR_PAIR(figure_next.figure[k - sdv][l]));
              printw("  ");
              attroff(COLOR_PAIR(figure_next.figure[k - sdv][l]));
            }
          }
        }
      }
    }
    printw("\n");
  }
}

void begin_field() {
  // WINDOW *win_start = newwin(20, 20, 1, 1);
  // wbkgdset(win_start, COLOR_PAIR(1));
  // box(win_start, 0, 0);
  mvprintw(10, 18, "TETRIS");
  mvprintw(12, 15, "PRESS ANY KEY");
  mvprintw(14, 17, "TO START!");
  // wrefresh(win_start);
  fflush(stdout);
  nodelay(stdscr, FALSE);
  getch();
  nodelay(stdscr, TRUE);
  clear();
}

void pause_output() {
  // WINDOW *win_start = newwin(20, 20, 1, 1);
  mvprintw(10, 18, "TETRIS");
  mvprintw(12, 15, "PRESS ANY KEY");
  mvprintw(14, 16, "TO CONTINUE!");
  fflush(stdout);
  nodelay(stdscr, FALSE);
  getch();
  nodelay(stdscr, TRUE);
  clear();
}

void end_output(components_game *result) {
  // WINDOW *win_start = newwin(20, 20, 1, 1);
  mvprintw(10, 16, "GAME OVER!");
  mvprintw(12, 16, "YOUR SCORE - %d", result->score);
  mvprintw(14, 15, "PRESS ANY KEY TO CONTINUE!");
  mvprintw(16, 16, "OR 'q' TO EXIT");
  fflush(stdout);
  nodelay(stdscr, FALSE);
  if (getch() == 113) {
    result->end_game = 1;
    result->over_app = 1;
  }
  nodelay(stdscr, TRUE);
  clear();
}

void function_of_view_figure(buf_field buf_field, components_game components,
                             figure_of_game figure_next) {
  if (components.stop == 1) {
    pause_output();
  }

  if (components.down != 1) {
    struct timespec tw = {0, 899999999 / (components.level + 1)};
    output_game_figures(buf_field, components, figure_next);
    refresh();
    nanosleep(&tw, NULL);
    clear();
  }
}