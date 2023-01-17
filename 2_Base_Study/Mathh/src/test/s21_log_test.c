#include "test.h"

START_TEST(log_check) {
  ck_assert_float_eq(s21_log(1.0), log(1.0));
  ck_assert_ldouble_eq(s21_log(0.0), log(0.0));
  ck_assert_ldouble_nan(s21_log(-1.0));
  ck_assert_ldouble_nan(log(-1.0));
  ck_assert_float_eq(s21_log(10000.0), log(10000.0));
  ck_assert_ldouble_eq_tol(s21_log(S21_PI / 2), log(S21_PI / 2), 10);
  ck_assert_ldouble_nan(s21_log(-3 * S21_PI / 4));
  ck_assert_ldouble_nan(log(-3 * S21_PI / 4));
  ck_assert_ldouble_nan(s21_log(-10000.0));
  ck_assert_ldouble_nan(log(-10000.0));
  ck_assert_ldouble_nan(s21_log(-1.0 / 0.0));
  ck_assert_ldouble_nan(log(-1.0 / 0.0));
  ck_assert_ldouble_eq(s21_log(1.0 / 0.0), log(1.0 / 0.0));
  ck_assert_ldouble_nan(s21_log(NaN));
  ck_assert_ldouble_nan(log(NaN));
}
END_TEST

Suite *s21_log_suite() {
  Suite *s = suite_create("log_suit");
  TCase *tc = tcase_create("log_test");
  tcase_add_test(tc, log_check);
  suite_add_tcase(s, tc);
  return s;
}