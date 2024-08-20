#include "./brick_game/tetris/S21_backend.h"
#include "./gui/cli/S21_frontend.h"
int main() {
  turn_on_all_ncurses();
  components_game components = {0};
  figure_of_game figure_game = {0};
  figure_of_game figure_next = {0};
  buf_field buf_field = {0};
  int fall = 0;
  int x = WIDTH / 2;
  int y = 0;
  int count_rows = 0;
  while (components.over_app != 1) {
    begin_field();
    begining_game(&components);
    while (components.end_game != 1) {
      create_figures(&figure_game, &figure_next);
      zeros_help_function(&fall, &x, &y, &count_rows, &components);
      while (fall != 1 && components.end_game != 1) {
        change_the_field(&components, &figure_game, &buf_field, &x, &y, &fall,
                         &count_rows);
        function_of_view_figure(buf_field, components, figure_next);
        key_action(&components, &figure_game, &x, &y);
        move_down(&y);
      }
      equal_fields_back(&buf_field, &components);
      cline_field(&components);
    }
    change_max_score(&components);
    end_output(&components);
    end_game(&components, &figure_game, &figure_next);
  }
  components.end_game = 0;
  endwin();
  return 0;
}
