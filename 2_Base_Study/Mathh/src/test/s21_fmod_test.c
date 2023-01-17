#include "test.h"

START_TEST(fmod_check) {
  ck_assert_ldouble_eq(s21_fmod(0.0, 1.0), fmod(0.0, 1.0));
  ck_assert_ldouble_eq(s21_fmod(1.0, 21.0), fmod(1.0, 21.0));
  ck_assert_ldouble_eq(s21_fmod(-1555.999, 44.532), fmod(-1555.999, 44.532));
  ck_assert_ldouble_eq(s21_fmod(12.0, 53), fmod(12.0, 53));
  ck_assert_ldouble_eq(s21_fmod(0.00000001, 5352.6), fmod(0.00000001, 5352.6));
  ck_assert_ldouble_nan(s21_fmod(12.0, 0));
  ck_assert_ldouble_nan(fmod(12.0, 0));
  ck_assert_ldouble_nan(fmod(-INF, 10));
  ck_assert_ldouble_nan(s21_fmod(-INF, 10));
  ck_assert_ldouble_eq(s21_fmod(10, INF), fmod(10, INF));
  ck_assert_ldouble_nan(fmod(-INF, -INF));
  ck_assert_ldouble_nan(s21_fmod(-INF, -INF));
  ck_assert_ldouble_nan(fmod(NaN, NaN));
  ck_assert_ldouble_nan(s21_fmod(NaN, NaN));
  ck_assert_ldouble_nan(fmod(10, NaN));
  ck_assert_ldouble_nan(s21_fmod(10, NaN));
}
END_TEST

Suite *s21_fmod_suite() {
  Suite *s = suite_create("fmod_suit");
  TCase *tc = tcase_create("fmod_test");
  tcase_add_test(tc, fmod_check);
  suite_add_tcase(s, tc);
  return s;
}