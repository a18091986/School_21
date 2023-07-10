#include "test.h"

// 3+(-4)*sin(3+5)*2/(1-5)^2^3
// 15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))

START_TEST(hard_test_1) {
  char input[128] =
      "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";
  char x[128] = "";

  char output[128] = {0};
  double expect = 15.0 / (7 - (1 + 1)) * 3 -
                  (2 + (1 + 1)) * 15.0 / (7 - (200 + 1)) * 3 -
                  (2 + (1 + 1)) * (15.0 / (7 - (1 + 1)) * 3 - (2 + (1 + 1)) +
                                   15.0 / (7 - (1 + 1)) * 3 - (2 + (1 + 1)));

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(hard_test_2) {
  char input[128] = "3+(-4)*sin(3+5)*2/(1-5)^2^2";
  char x[128] = "";

  char output[128] = {0};
  double expect = 3 + (-4) * sin(3.0 + 5) * 2.0 / pow(pow((1 - 5.0), 2.0), 2.0);

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

Suite *test_hard_equations_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("hard_equations_test");
  /* Core test case */
  tc = tcase_create("hard_equations_tc");

  tcase_add_test(tc, hard_test_1);
  tcase_add_test(tc, hard_test_2);

  suite_add_tcase(s, tc);

  return s;
}
