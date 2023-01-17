#include "test.h"

START_TEST(exp_check) {
  ck_assert_float_eq(exp(-13.54), s21_exp(-13.54));
  ck_assert_float_eq(exp(13.54), s21_exp(13.54));
  ck_assert_float_eq(exp(-0.54), s21_exp(-0.54));
  ck_assert_float_eq(exp(1000), s21_exp(1000));
  ck_assert_float_eq(exp(1), s21_exp(1));
  ck_assert_float_eq(exp(2), s21_exp(2));
  ck_assert_float_eq(exp(-1), s21_exp(-1));
  ck_assert_float_eq(exp(0), s21_exp(0));
  ck_assert_float_eq(exp(710), s21_exp(710));
  ck_assert_float_eq(exp(1.2345), s21_exp(1.2345));
  ck_assert_float_eq(exp(1.23454656768), s21_exp(1.23454656768));
  ck_assert_ldouble_nan(s21_exp(NaN));
  ck_assert_ldouble_nan(exp(NaN));
  ck_assert_ldouble_eq(s21_exp(-INF), exp(-INF));
}
END_TEST

Suite *s21_exp_suite() {
  Suite *s = suite_create("exp_suit");
  TCase *tc = tcase_create("exp_test");
  tcase_add_test(tc, exp_check);
  suite_add_tcase(s, tc);
  return s;
}