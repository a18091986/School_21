#include "test.h"

START_TEST(cos_check) {
  ck_assert_float_eq(s21_cos(1.0), cos(1.0));
  ck_assert_float_eq(s21_cos(-1.0), cos(-1.0));
  ck_assert_ldouble_eq(s21_cos(0.0), cos(0.0));
  ck_assert_float_eq(s21_cos(10000.0), cos(10000.0));
  ck_assert_ldouble_eq_tol(s21_cos(S21_PI / 2), cos(S21_PI / 2), 10);
  ck_assert_ldouble_eq_tol(s21_cos(-3 * S21_PI / 4), cos(-3 * S21_PI / 4), 10);
  ck_assert_float_eq(s21_cos(-10000.0), cos(-10000.0));
  ck_assert_ldouble_nan(s21_acos(-1.0 / 0.0));
  ck_assert_ldouble_nan(cos(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_cos(NaN));
  ck_assert_ldouble_nan(cos(NaN));
}
END_TEST

Suite *s21_cos_suite() {
  Suite *s = suite_create("cos_suit");
  TCase *tc = tcase_create("cos_test");
  tcase_add_test(tc, cos_check);
  suite_add_tcase(s, tc);
  return s;
}