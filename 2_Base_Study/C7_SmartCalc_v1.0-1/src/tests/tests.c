#include "tests.h"

START_TEST(back_1) {
  int err = 0;
  double result = 0.0;
  char polish_string[512] = {'\0'};
  double x = 1.1;
  double right_res = 11.0;

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  char *input_string = "5 + 6\n";

  result = back_process(input_string, polish_string, x, &q_in, &q_polish, s_in,
                        s_pol, &err);

  // int code = parse_to_tokens(str, &res);

  // ck_assert_int_eq(code, SUCCESS);
  // queue *rpn;
  // rpn = make_rpn(res, &code);
  // ck_assert_int_eq(code, SUCCESS);
  // double dres = calc_rpn(rpn, 0, &code);
  // ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(result, right_res, EPS);

  // free_queue(&res);
  // free_queue(&rpn);
}
END_TEST

START_TEST(back_2) {
  int err = 0;
  double result = 0.0;
  char polish_string[512] = {'\0'};
  double x = 2;
  double right_res = 8.0;

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  char *input_string = "x + 6\n";

  result = back_process(input_string, polish_string, x, &q_in, &q_polish, s_in,
                        s_pol, &err);

  // int code = parse_to_tokens(str, &res);

  // ck_assert_int_eq(code, SUCCESS);
  // queue *rpn;
  // rpn = make_rpn(res, &code);
  // ck_assert_int_eq(code, SUCCESS);
  // double dres = calc_rpn(rpn, 0, &code);
  // ck_assert_int_eq(code, SUCCESS);

  ck_assert_double_eq_tol(result, right_res, EPS);

  // free_queue(&res);
  // free_queue(&rpn);
}
END_TEST

Suite *calc_suite() {
  Suite *s = suite_create("calc_suite");
  TCase *t1 = tcase_create("back_1");
  suite_add_tcase(s, t1);
  tcase_add_test(t1, back_1);

  TCase *t2 = tcase_create("back_2");
  suite_add_tcase(s, t2);
  tcase_add_test(t2, back_2);
  return s;
}

int main() {
  int no_failed = 0;
  Suite *s = calc_suite();
  SRunner *runner = srunner_create(s);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, 2);
  no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? 0 : 1;
}
