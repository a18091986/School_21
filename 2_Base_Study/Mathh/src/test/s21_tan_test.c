#include "test.h"

START_TEST(tan_check) {
  ck_assert_ldouble_eq(s21_tan(0.0), tan(0.0));
  ck_assert_float_eq(s21_tan(1.0), tan(1.0));
  ck_assert_ldouble_eq_tol(s21_tan(-4234235223.0), tan(-4234235223.0), 10);
  ck_assert_ldouble_eq_tol(s21_tan(-1555.999), tan(-1555.999), 10);
  ck_assert_ldouble_eq_tol(s21_tan(S21_PI / 4), tan(S21_PI / 4), 10);
  ck_assert_ldouble_eq_tol(s21_tan(12.0), tan(12.0), 10);
  ck_assert_ldouble_nan(s21_tan(0.0 / 0.0));
  ck_assert_ldouble_nan(s21_tan(-1.0 / 0.0));
  ck_assert_ldouble_nan(tan(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_tan(INF));
  ck_assert_ldouble_nan(tan(INF));
  ck_assert_ldouble_nan(s21_tan(NaN));
  ck_assert_ldouble_nan(tan(NaN));
}
END_TEST

Suite *s21_tan_suite() {
  Suite *s = suite_create("tan_suit");
  TCase *tc = tcase_create("tan_test");
  tcase_add_test(tc, tan_check);
  suite_add_tcase(s, tc);
  return s;
}