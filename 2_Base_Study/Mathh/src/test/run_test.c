#include "test.h"

int main(void) {
  int fc = 1;
  runTest(s21_abs_suite(), &fc);
  runTest(s21_fabs_suite(), &fc);
  runTest(s21_fmod_suite(), &fc);
  runTest(s21_floor_suite(), &fc);
  runTest(s21_ceil_suite(), &fc);
  runTest(s21_pow_suite(), &fc);
  runTest(s21_sin_suite(), &fc);
  runTest(s21_sqrt_suite(), &fc);
  runTest(s21_tan_suite(), &fc);
  runTest(s21_acos_suite(), &fc);
  runTest(s21_cos_suite(), &fc);
  runTest(s21_exp_suite(), &fc);
  runTest(s21_log_suite(), &fc);
  runTest(s21_asin_suite(), &fc);
  runTest(s21_atan_suite(), &fc);
  return fc;
}

void runTest(Suite *suit, int *fc) {
  SRunner *sr = srunner_create(suit);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  int f = srunner_ntests_failed(sr);
  if (*fc != 0) *fc = f;
  srunner_free(sr);
}