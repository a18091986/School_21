#include "test.h"

START_TEST(sin_check) {
  ck_assert_float_eq(s21_sin(0.0), sin(0.0));
  ck_assert_float_eq(s21_sin(1.0), sin(1.0));
  ck_assert_ldouble_eq_tol(s21_sin(-4234235223.0), sin(-4234235223.0), 10);
  ck_assert_ldouble_eq_tol(s21_sin(-1555.999), sin(-1555.999), 10);
  ck_assert_ldouble_eq_tol(s21_sin(12.0), sin(12.0), 10);
  ck_assert_float_eq(s21_sin(-1555.999), sin(-1555.999));
  ck_assert_float_eq(s21_sin(12.0), sin(12.0));
  ck_assert_ldouble_nan(s21_sin(-1.0 / 0.0));
  ck_assert_ldouble_nan(sin(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_sin(0.0 / 0.0));
  ck_assert_ldouble_nan(sin(0.0 / 0.0));
  ck_assert_ldouble_nan(s21_sin(INF));
  ck_assert_ldouble_nan(sin(INF));
}
END_TEST

Suite *s21_sin_suite() {
  Suite *s = suite_create("sin_suit");
  TCase *tc = tcase_create("sin_test");
  tcase_add_test(tc, sin_check);
  suite_add_tcase(s, tc);
  return s;
}