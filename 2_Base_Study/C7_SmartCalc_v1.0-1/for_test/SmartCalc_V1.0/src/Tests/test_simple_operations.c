#include "test.h"

START_TEST(addition_test) {
  char input[128] = "1+2";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "3";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(subs_test) {
  char input[128] = "13-10";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "3";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(mul_test) {
  char input[128] = "2*75";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "150";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(div_test) {
  char input[128] = "10/4";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "2.5";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(mod_test) {
  char input[128] = "10mod4";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "2";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(zero_div_test) {
  char input[128] = "10/0";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Error";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(unary_minus_test) {
  char input[128] = "-5+3";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "-2";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(brackets_test) {
  char input[128] = "((5+3)-(-3))*(5+5)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "110";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(pow_test) {
  char input[128] = "4^2";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "16";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(multiple_pow_test) {
  char input[128] = "2^2^2";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "16";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(empty_brackets_test_1) {
  char input[128] = "()";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(empty_brackets_test_2) {
  char input[128] = ")(";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(too_much_brackets_test) {
  char input[128] = "(3+2))";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(too_few_brackets_test_1) {
  char input[128] = "(3+2";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(too_few_brackets_test_2) {
  char input[128] = "3+2)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(wrong_input_test_1) {
  char input[128] = "(3)(3+2)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(wrong_input_test_2) {
  char input[128] = "(3-)+(3+2)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(wrong_input_test_3) {
  char input[128] = "(3)+(3+2)-";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(wrong_input_test_4) {
  char input[128] = "(3)+(Pl+2)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(wrong_input_test_5) {
  char input[128] = "(3)+6(5+2)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(wrong_input_test_6) {
  char input[128] = "(3)6+(5+2)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

START_TEST(wrong_input_test_7) {
  char input[128] = "(3.5.6)+(5+2)";
  char x[128] = "";
  char output[128] = {0};
  char expect[] = "Invalid input";
  calculator(input, x, output);
  ck_assert_str_eq(output, expect);
}
END_TEST

Suite *test_simple_operations_suite(void) {
  Suite *s;
  TCase *tc;

  s = suite_create("simple_operations_test");
  /* Core test case */
  tc = tcase_create("simple_operations_tc");

  tcase_add_test(tc, addition_test);
  tcase_add_test(tc, subs_test);
  tcase_add_test(tc, mul_test);
  tcase_add_test(tc, div_test);
  tcase_add_test(tc, mod_test);
  tcase_add_test(tc, zero_div_test);
  tcase_add_test(tc, unary_minus_test);
  tcase_add_test(tc, brackets_test);
  tcase_add_test(tc, pow_test);
  tcase_add_test(tc, multiple_pow_test);
  tcase_add_test(tc, empty_brackets_test_1);
  tcase_add_test(tc, empty_brackets_test_2);
  tcase_add_test(tc, too_much_brackets_test);
  tcase_add_test(tc, too_few_brackets_test_1);
  tcase_add_test(tc, too_few_brackets_test_2);
  tcase_add_test(tc, wrong_input_test_1);
  tcase_add_test(tc, wrong_input_test_2);
  tcase_add_test(tc, wrong_input_test_3);
  tcase_add_test(tc, wrong_input_test_4);
  tcase_add_test(tc, wrong_input_test_5);
  tcase_add_test(tc, wrong_input_test_6);
  tcase_add_test(tc, wrong_input_test_7);

  suite_add_tcase(s, tc);

  return s;
}
