#include <ncurses.h>
#include <unistd.h>

#include "../../brick_game/tetris/S21_backend.h"
void output_game(components_game *result);
void output_game_figures(buf_field buf_field, components_game result,
                         figure_of_game figure_next);
void begin_field();
void pause_output();
void end_output(components_game *result);
void turn_on_all_ncurses();
void function_of_view_figure(buf_field buf_field, components_game components,
                             figure_of_game figure_next);