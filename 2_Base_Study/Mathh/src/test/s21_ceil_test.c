#include "test.h"

START_TEST(ceil_check) {
  ck_assert_ldouble_eq(s21_ceil(1.0), ceil(1.0));
  ck_assert_ldouble_eq(s21_ceil(-1.0), ceil(-1.0));
  ck_assert_ldouble_eq(s21_ceil(0.0), ceil(0.0));
  ck_assert_ldouble_eq(s21_ceil(21e-11), ceil(21e-11));
  ck_assert_ldouble_eq(s21_ceil(-1000000000000), ceil(-1000000000000));
  ck_assert_ldouble_eq(s21_ceil(20), ceil(20));
  ck_assert_ldouble_eq(s21_ceil(0.4), ceil(0.4));
  ck_assert_ldouble_nan(s21_cos(NaN));
  ck_assert_ldouble_nan(cos(NaN));
}
END_TEST

Suite *s21_ceil_suite() {
  Suite *s = suite_create("ceil_suit");
  TCase *tc = tcase_create("ceil_test");
  tcase_add_test(tc, ceil_check);
  suite_add_tcase(s, tc);
  return s;
}