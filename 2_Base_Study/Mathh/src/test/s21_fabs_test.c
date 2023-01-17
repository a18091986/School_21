#include "test.h"

START_TEST(fabs_check) {
  ck_assert_ldouble_eq(s21_fabs(1.0), fabs(1.0));
  ck_assert_ldouble_eq(s21_fabs(-423423523523523.0), fabs(-423423523523523.0));
  ck_assert_ldouble_eq(s21_fabs(-1555.999), fabs(-1555.999));
  ck_assert_ldouble_eq(s21_fabs(12.0), fabs(12.0));
  ck_assert_ldouble_eq(s21_fabs(0.00000001), fabs(0.00000001));
  ck_assert_ldouble_eq(s21_fabs(-INF), fabs(-INF));
  ck_assert_ldouble_nan(s21_fabs(NaN));
  ck_assert_ldouble_nan(s21_fabs(NaN));
}
END_TEST

Suite *s21_fabs_suite() {
  Suite *s = suite_create("fabs_suit");
  TCase *tc = tcase_create("fabs_test");
  tcase_add_test(tc, fabs_check);
  suite_add_tcase(s, tc);
  return s;
}