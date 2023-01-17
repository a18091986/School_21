#include "test.h"

START_TEST(asin_check) {
  ck_assert_float_eq(s21_asin(1.0), asin(1.0));
  ck_assert_ldouble_eq_tol(s21_asin(0.7), asin(0.7), 6);
  ck_assert_ldouble_eq(s21_asin(0.0), asin(0.0));
  ck_assert_ldouble_nan(s21_asin(10000.0));
  ck_assert_ldouble_nan(asin(10000.0));
  ck_assert_ldouble_nan(s21_asin(-3 * S21_PI / 4));
  ck_assert_ldouble_nan(asin(-3 * S21_PI / 4));
  ck_assert_ldouble_nan(s21_asin(-10000.0));
  ck_assert_ldouble_nan(asin(-10000.0));
  ck_assert_ldouble_nan(s21_asin(-1.0 / 0.0));
  ck_assert_ldouble_nan(asin(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_asin(1.0 / 0.0));
  ck_assert_ldouble_nan(asin(1.0 / 0.0));
  ck_assert_ldouble_nan(s21_asin(0.0 / 0.0));
  ck_assert_ldouble_nan(asin(0.0 / 0.0));
}
END_TEST

Suite *s21_asin_suite() {
  Suite *s = suite_create("asin_suit");
  TCase *tc = tcase_create("asin_test");
  tcase_add_test(tc, asin_check);
  suite_add_tcase(s, tc);
  return s;
}