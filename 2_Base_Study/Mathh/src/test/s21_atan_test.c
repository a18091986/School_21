#include "test.h"

START_TEST(atan_check) {
  ck_assert_ldouble_eq(s21_atan(0.0), atan(0.0));
  ck_assert_float_eq(s21_atan(1.0), atan(1.0));
  ck_assert_ldouble_eq_tol(s21_sin(-4234235223.0), sin(-4234235223.0), 10);
  ck_assert_ldouble_eq_tol(s21_sin(-1555.999), sin(-1555.999), 10);
  ck_assert_ldouble_eq_tol(s21_atan(S21_PI / 4), atan(S21_PI / 4), 10);
  ck_assert_ldouble_eq_tol(s21_atan(12.0), atan(12.0), 10);
  ck_assert_ldouble_nan(s21_atan(0.0 / 0.0));
  // ck_assert_ldouble_nan(s21_atan(-1.0 / 0.0));
  // ck_assert_ldouble_nan(atan(-1.0 / 0.0));
  // ck_assert_ldouble_nan(s21_atan(INF));
  // ck_assert_ldouble_nan(atan(INF));
  ck_assert_ldouble_nan(s21_atan(NaN));
  ck_assert_ldouble_nan(atan(NaN));
}
END_TEST

Suite *s21_atan_suite() {
  Suite *s = suite_create("atan_suit");
  TCase *tc = tcase_create("atan_test");
  tcase_add_test(tc, atan_check);
  suite_add_tcase(s, tc);
  return s;
}