#include "test.h"

START_TEST(tan_test) {
  char input[128] = "tan(Pi/4)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "1";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(cos_test) {
  char input[128] = "cos(Pi/3)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "0.5";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(sin_test) {
  char input[128] = "sin(Pi/6)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "0.5";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(tan_undet_test) {
  char input[128] = "tan(Pi/2)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Error";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(cos_zero_test) {
  char input[128] = "cos(Pi/2)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "0";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(sin_zero_test) {
  char input[128] = "sin(Pi)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "0";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(tan_zero_test) {
  char input[128] = "tan(Pi)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "0";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(acos_test) {
  char input[128] = "acos(-1)";
  char x[128] = "";
  char output[128] = {0};
  double expect = acos(-1);
  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(asin_test) {
  char input[128] = "asin(1/2)";
  double expect = asin(1.0 / 2);

  char x[128] = "";
  char output[128] = {0};

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(atan_test) {
  char input[128] = "atan(-1)";
  double expect = atan(-1.0);

  char x[128] = "";
  char output[128] = {0};

  calculator(input, x, output);
  double got = atof(output);
  ck_assert_double_eq_tol(got, expect, EPS_FOR_TEST);
}
END_TEST

START_TEST(asin_bound_test) {
  char input[128] = "asin(6)";
  char x[128] = "";

  char output[128] = {0};
  char expect[128] = "Error";

  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(acos_bound_test) {
  char input[128] = "acos(-1.2)";
  char x[128] = "";

  char output[128] = {0};
  char expect[128] = "Error";

  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(sqrt_wrong_test) {
  char input[128] = "sqrt(-9)";
  char x[128] = "";

  char output[128] = {0};
  char expect[128] = "Error";

  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(ln_wrong_test) {
  char input[128] = "ln(-9)";
  char x[128] = "";

  char output[128] = {0};
  char expect[128] = "Error";

  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(mod_wrong_test) {
  char input[128] = "9mod0";
  char x[128] = "";

  char output[128] = {0};
  char expect[128] = "Error";

  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

Suite *test_trigonometry_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("trigonometry_test");
  /* Core test case */
  tc = tcase_create("trigonometry_tc");

  tcase_add_test(tc, tan_test);
  tcase_add_test(tc, cos_test);
  tcase_add_test(tc, sin_test);
  tcase_add_test(tc, tan_undet_test);
  tcase_add_test(tc, cos_zero_test);
  tcase_add_test(tc, sin_zero_test);
  tcase_add_test(tc, tan_zero_test);
  tcase_add_test(tc, acos_test);
  tcase_add_test(tc, asin_test);
  tcase_add_test(tc, atan_test);
  tcase_add_test(tc, asin_bound_test);
  tcase_add_test(tc, acos_bound_test);
  tcase_add_test(tc, sqrt_wrong_test);
  tcase_add_test(tc, ln_wrong_test);
  tcase_add_test(tc, mod_wrong_test);

  suite_add_tcase(s, tc);

  return s;
}
