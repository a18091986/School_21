#include "test.h"

START_TEST(acos_check) {
  ck_assert_ldouble_eq(s21_acos(1.0), acos(1.0));
  ck_assert_ldouble_eq(s21_acos(-1.0), acos(-1.0));
  ck_assert_ldouble_eq(s21_acos(0.0), acos(0.0));
  ck_assert_ldouble_nan(s21_acos(-4234235223.0));
  ck_assert_ldouble_nan(s21_acos(5));
  ck_assert_ldouble_nan(acos(5));
  ck_assert_ldouble_nan(s21_acos(13.02));
  ck_assert_ldouble_nan(acos(13.02));
  ck_assert_ldouble_nan(s21_acos(-INF));
  ck_assert_ldouble_nan(acos(-INF));
  ck_assert_ldouble_nan(s21_acos(NaN));
  ck_assert_ldouble_nan(acos(NaN));
}
END_TEST

Suite *s21_acos_suite() {
  Suite *s = suite_create("acos_suit");
  TCase *tc = tcase_create("acos_test");
  tcase_add_test(tc, acos_check);
  suite_add_tcase(s, tc);
  return s;
}