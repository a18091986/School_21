#include "test.h"

START_TEST(sqrt_test) {
  char input[128] = "sqrt(198)";
  double expect = sqrt(198);

  char x[128] = "";
  char output[128] = {0};

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(ln_test) {
  char input[128] = "log(5/2)";
  double expect = log10(5.0 / 2);

  char x[128] = "";
  char output[128] = {0};

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(log_test) {
  char input[128] = "ln(e)";
  double expect = log(M_E);

  char x[128] = "";
  char output[128] = {0};

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

Suite *test_sqrt_log_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("sqrt_log_test");
  /* Core test case */
  tc = tcase_create("sqrt_log_tc");

  tcase_add_test(tc, sqrt_test);
  tcase_add_test(tc, ln_test);
  tcase_add_test(tc, log_test);

  suite_add_tcase(s, tc);

  return s;
}
