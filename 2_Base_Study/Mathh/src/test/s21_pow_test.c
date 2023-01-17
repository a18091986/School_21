#include "test.h"

START_TEST(pow_check) {
  ck_assert_ldouble_eq(s21_pow(0.0, 1.0), pow(0.0, 1.0));
  ck_assert_ldouble_eq(s21_pow(1.0, 21.0), pow(1.0, 21.0));
  ck_assert_ldouble_nan(s21_pow(-423423523523523.0, 33.33));
  ck_assert_ldouble_nan(s21_pow(-1555.999, 44.532));
  ck_assert_float_eq(s21_pow(12.0, 5), pow(12.0, 5));
  ck_assert_ldouble_eq(s21_pow(0, 32), pow(0, 32));
  ck_assert_ldouble_eq(s21_pow(-1.0 / 0.0, 13), pow(-1.0 / 0.0, 13));
  ck_assert_ldouble_eq(pow(0.0 / 0.0, 0), s21_pow(0.0 / 0.0, 0));
  ck_assert_ldouble_eq(s21_pow(0.0 / 0.0, 0.0), pow(0.0 / 0.0, 0.0));
}
END_TEST

Suite *s21_pow_suite() {
  Suite *s = suite_create("pow_suit");
  TCase *tc = tcase_create("pow_test");
  tcase_add_test(tc, pow_check);
  suite_add_tcase(s, tc);
  return s;
}