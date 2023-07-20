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

START_TEST(back_3) {
  int err = 0;
  double result = 0.0;
  char polish_string[512] = {'\0'};
  double x = 3.14;
  double right_res = -6.1055400;

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  char *input_string = "tan(sin(cos(x^2)*3)-1)\n";

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

START_TEST(back_4) {
  int err = 0;
  double result = 0.0;
  char polish_string[512] = {'\0'};
  double x = 3.14;
  double right_res = -6.1055400;

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  char *input_string = "tan(sin(cos(x^2)*3)-1)\n";

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

START_TEST(back_5) {
  int err = 0;
  double result = 0.0;
  char polish_string[512] = {'\0'};
  double x = 37;
  double right_res = -1.0816691;

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  char *input_string = "log(asin(sqrt(x)-6))\n";

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

START_TEST(back_6) {
  int err = 0;
  double result = 0.0;
  char polish_string[512] = {'\0'};
  double x = 4.0;
  double right_res = 1.0;

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  char *input_string =
      "(acos(1) + 10.0 mod 2 + sqrt(x) + ln(1) + atan(0)) / 2.0\n";

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
  freeStack(s_in);
}
END_TEST

START_TEST(back_7) {
  int err = 0;
  char polish_string[512] = {'\0'};
  double x = 4.0;

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  char *input_string = "10+3)\n";

  back_process(input_string, polish_string, x, &q_in, &q_polish, s_in, s_pol,
               &err);

  ck_assert_int_eq(err, 1);

  // int code = parse_to_tokens(str, &res);

  // ck_assert_int_eq(code, SUCCESS);
  // queue *rpn;
  // rpn = make_rpn(res, &code);
  // ck_assert_int_eq(code, SUCCESS);
  // double dres = calc_rpn(rpn, 0, &code);
  // ck_assert_int_eq(code, SUCCESS);

  // ck_assert_double_eq_tol(result, right_res, EPS);

  // free_queue(&res);
  // free_queue(&rpn);
  freeStack(s_in);
}
END_TEST

START_TEST(back_8) {
  int err = 0;
  double result = 0.0;
  char polish_string[512] = {'\0'};
  double x = 4.0;
  double right_res = 256;

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  char *input_string = "2^(2^3)\n";

  result = back_process(input_string, polish_string, x, &q_in, &q_polish, s_in,
                        s_pol, &err);

  // ck_assert_int_eq(err, 1);

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
  freeStack(s_in);
}
END_TEST

START_TEST(back_9) {
  int err = 0;
  char polish_string[512] = {'\0'};
  double x = 4.0;

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  char *input_string = "2 mod mod 2\n";

  back_process(input_string, polish_string, x, &q_in, &q_polish, s_in, s_pol,
               &err);

  ck_assert_int_eq(err, 1);

  // int code = parse_to_tokens(str, &res);

  // ck_assert_int_eq(code, SUCCESS);
  // queue *rpn;
  // rpn = make_rpn(res, &code);
  // ck_assert_int_eq(code, SUCCESS);
  // double dres = calc_rpn(rpn, 0, &code);
  // ck_assert_int_eq(code, SUCCESS);

  // ck_assert_double_eq_tol(result, right_res, EPS);

  // free_queue(&res);
  // free_queue(&rpn);
  // freeStack(s_in);
  // freeStack(s_pol);
  // free(input_string);
}
END_TEST

START_TEST(deposit_test) {
  char start[10] = "30000.00";
  char time[10] = "12";
  char dep_pct[10] = "8.3";
  char tax_pct[10] = "13.0";
  int pay_period = 1;
  int cap = 1;

  char plus_period[10] = "1";
  char plus_sum[10] = "1000";
  char minus_period[10] = "3";
  char minus_sum[10] = "500";

  double depo_result_sum_num;
  double depo_result_pct_num;
  double depo_result_tax_num;

  deposit(start, time, dep_pct, tax_pct, pay_period, cap, plus_period, plus_sum,
          minus_period, minus_sum, &depo_result_sum_num, &depo_result_pct_num,
          &depo_result_tax_num);

  printf("depo: %.8lf", depo_result_sum_num);
  ck_assert_double_eq_tol(depo_result_sum_num, 43156.54878560, EPS);
}
END_TEST

START_TEST(credit_test) {
  char credit_v[10] = "400000.00";
  char time[10] = "24";
  char credit_pct[10] = "12.0";

  int type = 1;

  double pay_month_f;
  double pay_month_l;
  double over_pay;
  double sum_pay;

  credit(credit_v, time, credit_pct, type, &pay_month_f, &pay_month_l,
         &over_pay, &sum_pay);

  ck_assert_double_eq_tol(pay_month_f, 18829.38888931, EPS);

  type = 0;
  credit(credit_v, time, credit_pct, type, &pay_month_f, &pay_month_l,
         &over_pay, &sum_pay);
  printf("pay_month_f: %.8lf", pay_month_f);
  ck_assert_double_eq_tol(pay_month_f, 20666.66666667, EPS);
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

  TCase *t3 = tcase_create("back_3");
  suite_add_tcase(s, t3);
  tcase_add_test(t3, back_3);

  TCase *t4 = tcase_create("back_4");
  suite_add_tcase(s, t4);
  tcase_add_test(t4, back_4);

  TCase *t5 = tcase_create("back_5");
  suite_add_tcase(s, t5);
  tcase_add_test(t5, back_5);

  TCase *t6 = tcase_create("back_6");
  suite_add_tcase(s, t6);
  tcase_add_test(t6, back_6);

  TCase *t7 = tcase_create("back_7");
  suite_add_tcase(s, t7);
  tcase_add_test(t7, back_7);

  TCase *t8 = tcase_create("back_8");
  suite_add_tcase(s, t8);
  tcase_add_test(t8, back_8);

  TCase *t9 = tcase_create("back_9");
  suite_add_tcase(s, t9);
  tcase_add_test(t9, back_9);

  TCase *t10 = tcase_create("deposit");
  suite_add_tcase(s, t10);
  tcase_add_test(t10, deposit_test);

  TCase *t11 = tcase_create("credit_test");
  suite_add_tcase(s, t11);
  tcase_add_test(t11, credit_test);

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
