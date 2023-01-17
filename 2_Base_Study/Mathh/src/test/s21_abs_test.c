#include "test.h"

START_TEST(abs_check) {
  ck_assert_int_eq(s21_abs(-1000), abs(-1000));
  ck_assert_int_eq(s21_abs(-1), abs(-1));
  ck_assert_int_eq(s21_abs(765756756), abs(765756756));
  ck_assert_int_eq(s21_abs(-2147483647), abs(-2147483647));
  ck_assert_int_eq(s21_abs(-0), abs(-0));
  ck_assert_int_eq(s21_abs(123456789), abs(123456789));
  ck_assert_int_eq(s21_abs(100), abs(100));
  ck_assert_int_eq(s21_abs(-100), abs(-100));
  ck_assert_int_eq(s21_abs(0), abs(0));
}
END_TEST

Suite *s21_abs_suite() {
  Suite *s = suite_create("abs_suit");
  TCase *tc = tcase_create("abs_test");
  tcase_add_test(tc, abs_check);
  suite_add_tcase(s, tc);
  return s;
}

// void runTest(Suite *suit, int *fc) {
//   SRunner *sr = srunner_create(suit);
//   srunner_set_fork_status(sr, CK_NOFORK);
//   srunner_run_all(sr, CK_NORMAL);
//   int f = srunner_ntests_failed(sr);
//   if (*fc != 0) *fc = f;
//   srunner_free(sr);
// }
// int main(void) {
//   int fc = 1;
//   runTest(s21_abs_suite(), &fc);
//   return fc;
// }
