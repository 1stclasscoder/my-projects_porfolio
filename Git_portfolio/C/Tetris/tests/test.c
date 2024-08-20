#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../brick_game/tetris/S21_backend.h"
#include "../gui/cli/S21_frontend.h"

START_TEST(test_1) {
  components_game components = {0};
  begining_game(&components);
  ck_assert_int_eq(components.end_game, 0);
}
END_TEST

START_TEST(test_2) {
  components_game components = {0};
  figure_of_game figure_game = {0};
  figure_of_game figure_next = {0};
  buf_field buf_field = {0};
  int fall = 0;
  int x = WIDTH / 2;
  int y = 0;
  int count_rows = 0;
  begining_game(&components);
  create_figures(&figure_game, &figure_next);
  zeros_help_function(&fall, &x, &y, &count_rows, &components);
  change_the_field(&components, &figure_game, &buf_field, &x, &y, &fall,
                   &count_rows);
  s21_transpose(&figure_game);
  move_left(&components, &figure_game, &x, &y);
  move_right(&components, &x, &y);
  move_down(&y);
  equal_fields_back(&buf_field, &components);
  cline_field(&components);
  change_max_score(&components);
  end_game(&components, &figure_game, &figure_next);
  ck_assert_int_eq(components.end_game, 0);
  ck_assert_int_eq(x, WIDTH / 2);
  ck_assert_int_eq(y, 1);
}
END_TEST

START_TEST(test_3) {
  components_game components = {0};
  begining_game(&components);
  cline_line(&components, 1);
  ck_assert_int_eq(components.end_game, 0);
}
END_TEST

START_TEST(test_4) {
  components_game components = {0};
  begining_game(&components);
  figure_of_game figure_game = {0};
  figure_of_game figure_next = {0};
  full_figure(&figure_game, 0);
  s21_remove_figure(&figure_game);
  full_figure(&figure_game, 1);
  s21_remove_figure(&figure_game);
  full_figure(&figure_game, 2);
  s21_remove_figure(&figure_game);
  full_figure(&figure_game, 3);
  s21_remove_figure(&figure_game);
  full_figure(&figure_game, 4);
  s21_remove_figure(&figure_game);
  full_figure(&figure_game, 5);
  s21_remove_figure(&figure_game);
  full_figure(&figure_game, 6);
  end_game(&components, &figure_game, &figure_next);
  ck_assert_int_eq(components.end_game, 0);
}
END_TEST

START_TEST(test_5) {
  components_game components = {0};
  begining_game(&components);
  figure_of_game figure_game = {0};
  figure_of_game figure_next = {0};
  create_figures(&figure_game, &figure_next);
  create_figures(&figure_game, &figure_next);
  end_game(&components, &figure_game, &figure_next);
  ck_assert_int_eq(components.end_game, 0);
}
END_TEST

START_TEST(test_6) {
  components_game components = {0};
  begining_game(&components);
  load_max_score(&components);
  ck_assert_int_eq(components.end_game, 0);
}
END_TEST

START_TEST(test_7) {
  components_game components = {0};
  figure_of_game figure_game = {0};
  figure_of_game figure_next = {0};
  buf_field buf_field = {0};
  int fall = 0;
  int x = WIDTH / 2;
  int y = 0;
  int count_rows = 0;
  begining_game(&components);
  create_figures(&figure_game, &figure_next);
  zeros_help_function(&fall, &x, &y, &count_rows, &components);
  change_the_field(&components, &figure_game, &buf_field, &x, &y, &fall,
                   &count_rows);
  key_action_do(&components, &figure_game, &x, &y, 260);
  key_action_do(&components, &figure_game, &x, &y, 259);
  key_action_do(&components, &figure_game, &x, &y, 261);
  key_action_do(&components, &figure_game, &x, &y, 113);
  key_action_do(&components, &figure_game, &x, &y, 258);
  key_action_do(&components, &figure_game, &x, &y, 32);
  end_game(&components, &figure_game, &figure_next);
  ck_assert_int_eq(components.stop, 1);
  ck_assert_int_eq(components.end_game, 1);
  ck_assert_int_eq(x, WIDTH / 2);
}
END_TEST

Suite* tetris_suite(void) {
  Suite* s = suite_create("Tetris");
  TCase* tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_1);
  tcase_add_test(tc_core, test_2);
  tcase_add_test(tc_core, test_3);
  tcase_add_test(tc_core, test_4);
  tcase_add_test(tc_core, test_5);
  tcase_add_test(tc_core, test_6);
  tcase_add_test(tc_core, test_7);
  suite_add_tcase(s, tc_core);
  return s;
}

int main(void) {
  Suite* s = tetris_suite();
  SRunner* sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}