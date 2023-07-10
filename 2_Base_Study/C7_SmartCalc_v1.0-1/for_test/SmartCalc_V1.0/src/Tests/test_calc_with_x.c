#include "test.h"

START_TEST(x_add_test) {
  char input[128] = "x+6";
  char x[128] = "4";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = x_test + 6.0;

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_sub_test) {
  char input[128] = "x-6";
  char x[128] = "4";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = x_test - 6.0;

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_mul_test) {
  char input[128] = "x*6";
  char x[128] = "4";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = x_test * 6.0;

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_sin_test) {
  char input[128] = "sin(x)";
  char x[128] = "4";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = sin(x_test);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_cos_test) {
  char input[128] = "cos(x)";
  char x[128] = "4";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = cos(x_test);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_tan_test) {
  char input[128] = "tan(x)";
  char x[128] = "4";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = tan(x_test);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_asin_test) {
  char input[128] = "asin(x)";
  char x[128] = "0.35";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = asin(x_test);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_acos_test) {
  char input[128] = "acos(x)";
  char x[128] = "0.35";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = acos(x_test);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_atan_test) {
  char input[128] = "atan(x)";
  char x[128] = "4";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = atan(x_test);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_sqrt_test) {
  char input[128] = "sqrt(x)";
  char x[128] = "3521";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = sqrt(x_test);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_log_test) {
  char input[128] = "log(x)";
  char x[128] = "4";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = log10(x_test);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_ln_test) {
  char input[128] = "ln(x)";
  char x[128] = "e";
  double x_test = M_E;

  char output[128] = {0};
  double expect = log(x_test);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_wrong_test) {
  char input[128] = "ln(x)";
  char x[128] = "ld";

  char output[128] = {0};
  char expect[128] = "Error";

  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(x_cos_pi_test) {
  char input[128] = "3.5-cos(x+Pi/e)";
  char x[128] = "-3";
  double x_test = atof(x);

  char output[128] = {0};
  double expect = 3.5 - cos(x_test + M_PI / M_E);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_cos_pi_test_2) {
  char input[128] = "3.5-cos(x+e)";
  char x[128] = "Pi";
  double x_test = M_PI;

  char output[128] = {0};
  double expect = 3.5 - cos(x_test + M_E);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(x_wrong_cos_pi_test) {
  char input[128] = "3.5-cos(x+Pi/e)";
  char x[128] = "Pl";

  char output[128] = {0};
  char expect[128] = "Error";

  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(copy_test) {
  char user_input[128] = "ln(x)+6+x+76/34*sqrt(ln(5))";
  Stack *input = initStack();
  convertInput(user_input, input);
  Stack *rpn = rpnConverter(input);
  reverseStack(rpn);
  Stack *copiedStack = copyStack(rpn);
  while (!isEmpty(rpn)) {
    char *peeks_got = pop(copiedStack);
    char *peeks_must = pop(rpn);
    ck_assert_str_eq(peeks_got, peeks_must);
    free(peeks_got);
    free(peeks_must);
  }
  freeStack(rpn);
  freeStack(input);
  freeStack(copiedStack);
}
END_TEST

Suite *test_calc_with_x_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("calc_with_x_test");
  /* Core test case */
  tc = tcase_create("calc_with_x_tc");

  tcase_add_test(tc, x_add_test);
  tcase_add_test(tc, x_sub_test);
  tcase_add_test(tc, x_mul_test);
  tcase_add_test(tc, x_sin_test);
  tcase_add_test(tc, x_cos_test);
  tcase_add_test(tc, x_tan_test);
  tcase_add_test(tc, x_asin_test);
  tcase_add_test(tc, x_acos_test);
  tcase_add_test(tc, x_atan_test);
  tcase_add_test(tc, x_sqrt_test);
  tcase_add_test(tc, x_log_test);
  tcase_add_test(tc, x_ln_test);
  tcase_add_test(tc, x_wrong_test);
  tcase_add_test(tc, x_cos_pi_test);
  tcase_add_test(tc, x_cos_pi_test_2);
  tcase_add_test(tc, x_wrong_cos_pi_test);
  tcase_add_test(tc, copy_test);

  suite_add_tcase(s, tc);

  return s;
}
