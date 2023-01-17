#include "test.h"
START_TEST(floor_check) {
  ck_assert_ldouble_eq(s21_floor(0.0), floor(0.0));
  ck_assert_ldouble_eq(s21_floor(1.0), floor(1.0));
  ck_assert_ldouble_eq(s21_floor(-423423523523523.0),
                       floor(-423423523523523.0));
  ck_assert_ldouble_eq(s21_floor(-1555.999), floor(-1555.999));
  ck_assert_ldouble_eq(s21_floor(12.0), floor(12.0));
  ck_assert_ldouble_eq(s21_floor(0.00000001), floor(0.00000001));
  ck_assert_ldouble_eq(s21_floor(-1.0 / 0.0), floor(-1.0 / 0.0));
  ck_assert_ldouble_nan(s21_floor(NaN));
  ck_assert_float_nan(floor(NaN));
}
END_TEST

Suite *s21_floor_suite() {
  Suite *s = suite_create("floor_suit");
  TCase *tc = tcase_create("floor_test");
  tcase_add_test(tc, floor_check);
  suite_add_tcase(s, tc);
  return s;
}