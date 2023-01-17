#include "test.h"

START_TEST(sqrt_check) {
  ck_assert_ldouble_eq(s21_sqrt(0.0), sqrt(0.0));
  ck_assert_float_eq(s21_sqrt(1.0), sqrt(1.0));
  ck_assert_ldouble_nan(s21_sqrt(-423423523523523.0));
  ck_assert_ldouble_nan(s21_sqrt(-1555.999));
  ck_assert_ldouble_eq(s21_sqrt(12.0), sqrt(12.0));
  ck_assert_float_eq(s21_sqrt(0.00000001), sqrt(0.00000001));
  ck_assert_ldouble_nan(s21_sqrt(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_sqrt(0.0 / 0.0));
  ck_assert_ldouble_eq(s21_sqrt(INF), sqrt(INF));
}
END_TEST

Suite *s21_sqrt_suite() {
  Suite *s = suite_create("sqrt_suit");
  TCase *tc = tcase_create("sqrt_test");
  tcase_add_test(tc, sqrt_check);
  suite_add_tcase(s, tc);
  return s;
}