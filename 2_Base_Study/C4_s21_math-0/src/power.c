#include "power.h"

int main() {

  printf("-----------------POW--------------------\n");

  for (double x = -1.4; x < 1.4; x += 0.2) {
    printf("x: %lf\n", x);
    for (double y = - 1.4; y < 1.4; y += 0.2) {
      long double built_in_pow = (long double)pow(x, y);
      // long double not_my_pow = s21_pow(x, y);
      long double my_pow = s21_pow_my(x, y);
      // printf("base: %lf, exp: %lf\n", x, y);
      // printf("My pow %Lf\n", my_pow);
      // printf("NotMy pow %Lf\n", not_my_pow);
      // printf("Pow %Lf\n", built_in_pow);
      if (CHECK_INF(built_in_pow)) {
        if (!CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y, built_in_pow, my_pow);
          }
      else if (!CHECK_INF(built_in_pow)) {
        if (CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y, built_in_pow, my_pow);
          }
      else if (CHECK_NAN(built_in_pow)) {
        if (!CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y, built_in_pow, my_pow);
          }
      else if (!CHECK_NAN(built_in_pow)) {
        if (CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y, built_in_pow, my_pow);
          }
      else {
        if ((built_in_pow - my_pow) > EPS_for_tests) {
                printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", 
                    x, y, built_in_pow, my_pow);
      }
      }
    }
  }

  double y_inf = INF;
  for (double x = -1.4; x < 1.4; x += 0.2) {
    printf("x: %lf, y: %lf\n", x, y_inf);
    long double built_in_pow = (long double)pow(x, y_inf);
    // long double not_my_pow = s21_pow(x, y);
    long double my_pow = s21_pow_my(x, y_inf);
    // printf("base: %lf, exp: %lf\n", x, y);
    // printf("My pow %Lf\n", my_pow);
    // printf("NotMy pow %Lf\n", not_my_pow);
    // printf("Pow %Lf\n", built_in_pow);
      if (CHECK_INF(built_in_pow)) {
        if (!CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y_inf, built_in_pow, my_pow);
          }
      else if (!CHECK_INF(built_in_pow)) {
        if (CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y_inf, built_in_pow, my_pow);
          }
      else if (CHECK_NAN(built_in_pow)) {
        if (!CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y_inf, built_in_pow, my_pow);
          }
      else if (!CHECK_NAN(built_in_pow)) {
        if (CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y_inf, built_in_pow, my_pow);
          }
      else {
        if ((built_in_pow - my_pow) > EPS_for_tests) {
                printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", 
                    x, y_inf, built_in_pow, my_pow);
      }
      }
    }

  double y_nan = NaN;
  for (double x = -1.4; x < 1.4; x += 0.2) {
    printf("x: %lf, y: %lf\n", x, y_nan);
    long double built_in_pow = (long double)pow(x, y_nan);
    // long double not_my_pow = s21_pow(x, y);
    long double my_pow = s21_pow_my(x, y_nan);
    // printf("base: %lf, exp: %lf\n", x, y);
    // printf("My pow %Lf\n", my_pow);
    // printf("NotMy pow %Lf\n", not_my_pow);
    // printf("Pow %Lf\n", built_in_pow);
      if (CHECK_INF(built_in_pow)) {
        if (!CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y_nan, built_in_pow, my_pow);
          }
      else if (!CHECK_INF(built_in_pow)) {
        if (CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y_nan, built_in_pow, my_pow);
          }
      else if (CHECK_NAN(built_in_pow)) {
        if (!CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y_nan, built_in_pow, my_pow);
          }
      else if (!CHECK_NAN(built_in_pow)) {
        if (CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x, y_nan, built_in_pow, my_pow);
          }
      else {
        if ((built_in_pow - my_pow) > EPS_for_tests) {
                printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", 
                    x, y_nan, built_in_pow, my_pow);
      }
      }
    }

  double x_inf = INF;
  for (double y = -1.4; y < 1.4; y += 0.2) {
    printf("x: %lf, y: %lf\n", x_inf, y);
    long double built_in_pow = (long double)pow(x_inf, y);
    // long double not_my_pow = s21_pow(x, y);
    long double my_pow = s21_pow_my(x_inf, y);
    // printf("base: %lf, exp: %lf\n", x, y);
    // printf("My pow %Lf\n", my_pow);
    // printf("NotMy pow %Lf\n", not_my_pow);
    // printf("Pow %Lf\n", built_in_pow);
      if (CHECK_INF(built_in_pow)) {
        if (!CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x_inf, y, built_in_pow, my_pow);
          }
      else if (!CHECK_INF(built_in_pow)) {
        if (CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x_inf, y, built_in_pow, my_pow);
          }
      else if (CHECK_NAN(built_in_pow)) {
        if (!CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x_inf, y, built_in_pow, my_pow);
          }
      else if (!CHECK_NAN(built_in_pow)) {
        if (CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x_inf, y, built_in_pow, my_pow);
          }
      else {
        if ((built_in_pow - my_pow) > EPS_for_tests) {
                printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", 
                    x_inf, y, built_in_pow, my_pow);
      }
      }
    }

  double x_nan = NaN;
  for (double y = -1.4; y < 1.4; y += 0.2) {
    printf("x: %lf, y: %lf\n", x_nan, y);
    long double built_in_pow = (long double)pow(x_nan, y);
    // long double not_my_pow = s21_pow(x, y);
    long double my_pow = s21_pow_my(x_nan, y);
    // printf("base: %lf, exp: %lf\n", x, y);
    // printf("My pow %Lf\n", my_pow);
    // printf("NotMy pow %Lf\n", not_my_pow);
    // printf("Pow %Lf\n", built_in_pow);
    if (CHECK_INF(built_in_pow)) {
        if (!CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x_nan, y, built_in_pow, my_pow);
          }
      else if (!CHECK_INF(built_in_pow)) {
        if (CHECK_INF(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x_nan, y, built_in_pow, my_pow);
          }
      else if (CHECK_NAN(built_in_pow)) {
        if (!CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x_nan, y, built_in_pow, my_pow);
          }
      else if (!CHECK_NAN(built_in_pow)) {
        if (CHECK_NAN(my_pow))
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x_nan, y, built_in_pow, my_pow);
          }
      else {
        if ((built_in_pow - my_pow) > EPS_for_tests) {
                printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", 
                    x_nan, y, built_in_pow, my_pow);
      }
      }
    }

  // **************************************************
  double x1 = NaN, y1 = NaN;
  printf("x: %lf, y: %lf\n", x1, y1);
  // **************************************************
  long double built_in_pow1 = (long double)pow(x1, y1);
  // long double not_my_pow1 = s21_pow(x1, y1);
  long double my_pow1 = s21_pow_my(x1, y1);
  // printf("My pow %Lf\n", my_pow1);
  // printf("NotMy pow %Lf\n", not_my_pow1);
  // printf("Pow %Lf\n", built_in_pow1);
  if (CHECK_INF(built_in_pow1)) {
    if (!CHECK_INF(my_pow1))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x1, y1, built_in_pow1, my_pow1);
  }
  else if (!CHECK_INF(built_in_pow1)) {
    if (CHECK_INF(my_pow1))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x1, y1, built_in_pow1, my_pow1);
  }
  else if (CHECK_NAN(built_in_pow1)) {
    if (!CHECK_NAN(my_pow1))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x1, y1, built_in_pow1, my_pow1);
  }
  else if (!CHECK_NAN(built_in_pow1)) {
    if (CHECK_NAN(my_pow1))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x1, y1, built_in_pow1, my_pow1);
  }
  else {
    if ((built_in_pow1 - my_pow1) > EPS_for_tests) {
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", 
              x1, y1, built_in_pow1, my_pow1);
  }
  }

  
  // **************************************************
  double x2 = NaN, y2 = INF;
  printf("x: %lf, y: %lf\n", x2, y2);
  // **************************************************
  long double built_in_pow2 = (long double)pow(x2, y2);
  // long double not_my_pow2 = s21_pow(x2, y2);
  long double my_pow2 = s21_pow_my(x2, y2);
  // printf("My pow %Lf\n", my_pow2);
  // printf("NotMy pow %Lf\n", not_my_pow1);
  // printf("Pow %Lf\n", built_in_pow2);
  if (CHECK_INF(built_in_pow2)) {
    if (!CHECK_INF(my_pow2))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x2, y2, built_in_pow2, my_pow2);
  }
  else if (!CHECK_INF(built_in_pow2)) {
    if (CHECK_INF(my_pow2))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x2, y2, built_in_pow2, my_pow2);
  }
  else if (CHECK_NAN(built_in_pow2)) {
    if (!CHECK_NAN(my_pow2))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x2, y2, built_in_pow2, my_pow2);
  }
  else if (!CHECK_NAN(built_in_pow2)) {
    if (CHECK_NAN(my_pow2))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x2, y2, built_in_pow2, my_pow2);
  }
  else {
    if ((built_in_pow2 - my_pow2) > EPS_for_tests) {
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", 
              x2, y2, built_in_pow2, my_pow2);
  }
  }

  // **************************************************
  double x3 = INF, y3 = NaN;
  printf("x: %lf, y: %lf\n", x3, y3);
  // **************************************************
  long double built_in_pow3 = (long double)pow(x3, y3);
  // long double not_my_pow3 = s21_pow(x3, y3);
  long double my_pow3 = s21_pow_my(x3, y3);
  // printf("My pow %Lf\n", my_pow3);
  // printf("NotMy pow %Lf\n", not_my_pow1);
  // printf("Pow %Lf\n", built_in_pow3);
  if (CHECK_INF(built_in_pow3)) {
    if (!CHECK_INF(my_pow3))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x3, y3, built_in_pow3, my_pow3);
  }
  else if (!CHECK_INF(built_in_pow3)) {
    if (CHECK_INF(my_pow3))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x3, y3, built_in_pow2, my_pow3);
  }
  else if (CHECK_NAN(built_in_pow3)) {
    if (!CHECK_NAN(my_pow3))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x3, y3, built_in_pow3, my_pow3);
  }
  else if (!CHECK_NAN(built_in_pow3)) {
    if (CHECK_NAN(my_pow3))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x3, y3, built_in_pow3, my_pow3);
  }
  else {
    if ((built_in_pow3 - my_pow3) > EPS_for_tests) {
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", 
              x3, y3, built_in_pow3, my_pow3);
  }
  }

  // **************************************************
  double x4 = INF, y4 = INF;
  printf("x: %lf, y: %lf\n", x4, y4);
  // **************************************************
  long double built_in_pow4 = (long double)pow(x4, y4);
  // long double not_my_pow4 = s21_pow(x4, y4);
  long double my_pow4 = s21_pow_my(x4, y4);
  // printf("My pow %Lf\n", my_pow4);
  // printf("NotMy pow %Lf\n", not_my_pow1);
  // printf("Pow %Lf\n", built_in_pow4);
  if (CHECK_INF(built_in_pow4)) {
    if (!CHECK_INF(my_pow4))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x4, y4, built_in_pow4, my_pow4);
  }
  else if (!CHECK_INF(built_in_pow4)) {
    if (CHECK_INF(my_pow4))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x4, y4, built_in_pow2, my_pow4);
  }
  else if (CHECK_NAN(built_in_pow4)) {
    if (!CHECK_NAN(my_pow4))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x4, y4, built_in_pow4, my_pow4);
  }
  else if (!CHECK_NAN(built_in_pow4)) {
    if (CHECK_NAN(my_pow4))
    printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", x4, y4, built_in_pow4, my_pow4);
  }
  else {
    if ((built_in_pow4 - my_pow4) > EPS_for_tests) {
          printf("%lf, %lf - FAIL - built_in_pow: %Lf, my_pow: %Lf\n", 
              x4, y4, built_in_pow4, my_pow4);
  }
  }

  printf("-----------------LOG--------------------\n");

  for (double x = -1.4; x < 1.4; x += 0.2) {
    printf("x: %lf\n", x);
    long double built_in_log = (long double)log(x);
    // long double not_my_pow = s21_pow(x, y);
    long double my_log = s21_log_my(x);
    // printf("base: %lf, exp: %lf\n", x, y);
    // printf("My pow %Lf\n", my_pow);
    // printf("NotMy pow %Lf\n", not_my_pow);
    // printf("Pow %Lf\n", built_in_pow);
    if (CHECK_INF(built_in_log)) {
      if (!CHECK_INF(my_log))
        printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x, built_in_log, my_log);
        }
    else if (!CHECK_INF(built_in_log)) {
      if (CHECK_INF(my_log))
        printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x, built_in_log, my_log);
        }
    else if (CHECK_NAN(built_in_log)) {
      if (!CHECK_NAN(my_log))
        printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x, built_in_log, my_log);
        }
    else if (!CHECK_NAN(built_in_log)) {
      if (CHECK_NAN(my_log))
        printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x, built_in_log, my_log);
        }
    else {
      if ((built_in_log - my_log) > EPS_for_tests) {
              printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", 
                  x, built_in_log, my_log);
    }
    }
  }

  // **************************************************
  double x5 = NaN;
  printf("x: %lf\n", x5);
  // **************************************************
  long double built_in_log5 = (long double)log(x5);
  // long double not_my_pow2 = s21_pow(x2, y2);
  long double my_log5 = s21_log_my(x5);
  // printf("My log %Lf\n", my_log2);
  // printf("NotMy log %Lf\n", not_my_log1);
  // printf("log %Lf\n", built_in_log2);
  if (CHECK_INF(built_in_log5)) {
    if (!CHECK_INF(my_log5))
    printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x5, built_in_log5, my_log5);
  }
  else if (!CHECK_INF(built_in_log5)) {
    if (CHECK_INF(my_log5))
    printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x5, built_in_log5, my_log5);  }
  else if (CHECK_NAN(built_in_log5)) {
    if (!CHECK_NAN(my_log5))
    printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x5, built_in_log5, my_log5);
  }
  else if (!CHECK_NAN(built_in_log5)) {
    if (CHECK_NAN(my_log5))
    printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x5, built_in_log5, my_log5);
  }
  else {
    if ((built_in_log5 - my_log5) > EPS_for_tests) {
          printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", 
              x5, built_in_log5, my_log5);
  }
  }

    // **************************************************
  double x6 = INF;
  printf("x: %lf\n", x6);
  // **************************************************
  long double built_in_log6 = (long double)log(x6);
  // long double not_my_pow2 = s21_pow(x2, y2);
  long double my_log6 = s21_log_my(x6);
  // printf("My log %Lf\n", my_log2);
  // printf("NotMy log %Lf\n", not_my_log1);
  // printf("log %Lf\n", built_in_log2);
  if (CHECK_INF(built_in_log6)) {
    if (!CHECK_INF(my_log6))
    printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x6, built_in_log6, my_log6);
  }
  else if (!CHECK_INF(built_in_log6)) {
    if (CHECK_INF(my_log6))
    printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x6, built_in_log6, my_log6);  }
  else if (CHECK_NAN(built_in_log6)) {
    if (!CHECK_NAN(my_log6))
    printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x6, built_in_log6, my_log6);
  }
  else if (!CHECK_NAN(built_in_log6)) {
    if (CHECK_NAN(my_log6))
    printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", x6, built_in_log6, my_log6);
  }
  else {
    if ((built_in_log6 - my_log6) > EPS_for_tests) {
          printf("%lf - FAIL - built_in_log: %Lf, my_log: %Lf\n", 
              x6, built_in_log6, my_log6);
  }
  }

  printf("-----------------EXP--------------------\n");

  for (double x = -1.4; x < 1.4; x += 0.2) {
    printf("x: %lf\n", x);
    long double built_in_exp = (long double)exp(x);
    // long double not_my_pow = s21_pow(x, y);
    long double my_exp = s21_exp_my(x);
    // printf("base: %lf, exp: %lf\n", x, y);
    // printf("My pow %Lf\n", my_pow);
    // printf("NotMy pow %Lf\n", not_my_pow);
    // printf("Pow %Lf\n", built_in_pow);
    if (CHECK_INF(built_in_exp)) {
      if (!CHECK_INF(my_exp))
        printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x, built_in_exp, my_exp);
        }
    else if (!CHECK_INF(built_in_exp)) {
      if (CHECK_INF(my_exp))
        printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x, built_in_exp, my_exp);
        }
    else if (CHECK_NAN(built_in_exp)) {
      if (!CHECK_NAN(my_exp))
        printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x, built_in_exp, my_exp);
        }
    else if (!CHECK_NAN(built_in_exp)) {
      if (CHECK_NAN(my_exp))
        printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x, built_in_exp, my_exp);
        }
    else {
      if ((built_in_exp - my_exp) > EPS_for_tests) {
              printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", 
                  x, built_in_exp, my_exp);
    }
    }
  }

  // **************************************************
  double x7 = NaN;
  printf("x: %lf\n", x7);
  // **************************************************
  long double built_in_exp7 = (long double)exp(x7);
  // long double not_my_pow2 = s21_pow(x2, y2);
  long double my_exp7 = s21_exp_my(x7);
  // printf("My exp %Lf\n", my_exp2);
  // printf("NotMy exp %Lf\n", not_my_exp1);
  // printf("exp %Lf\n", built_in_exp2);
  if (CHECK_INF(built_in_exp7)) {
    if (!CHECK_INF(my_exp7))
    printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x7, built_in_exp7, my_exp7);
  }
  else if (!CHECK_INF(built_in_exp7)) {
    if (CHECK_INF(my_exp7))
    printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x7, built_in_exp7, my_exp7);  }
  else if (CHECK_NAN(built_in_exp7)) {
    if (!CHECK_NAN(my_exp7))
    printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x7, built_in_exp7, my_exp7);
  }
  else if (!CHECK_NAN(built_in_exp7)) {
    if (CHECK_NAN(my_exp7))
    printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x7, built_in_exp7, my_exp7);
  }
  else {
    if ((built_in_exp7 - my_exp7) > EPS_for_tests) {
          printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", 
              x7, built_in_exp7, my_exp7);
  }
  }

    // **************************************************
  double x8 = INF;
  printf("x: %lf\n", x8);
  // **************************************************
  long double built_in_exp8 = (long double)exp(x8);
  // long double not_my_pow2 = s21_pow(x2, y2);
  long double my_exp8 = s21_exp_my(x8);
  // printf("My exp %Lf\n", my_exp2);
  // printf("NotMy exp %Lf\n", not_my_exp1);
  // printf("exp %Lf\n", built_in_exp2);
  if (CHECK_INF(built_in_exp8)) {
    if (!CHECK_INF(my_exp8))
    printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x8, built_in_exp8, my_exp8);
  }
  else if (!CHECK_INF(built_in_exp8)) {
    if (CHECK_INF(my_exp8))
    printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x8, built_in_exp8, my_exp8);  }
  else if (CHECK_NAN(built_in_exp8)) {
    if (!CHECK_NAN(my_exp8))
    printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x8, built_in_exp8, my_exp8);
  }
  else if (!CHECK_NAN(built_in_exp8)) {
    if (CHECK_NAN(my_exp8))
    printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", x8, built_in_exp8, my_exp8);
  }
  else {
    if ((built_in_exp8 - my_exp8) > EPS_for_tests) {
          printf("%lf - FAIL - built_in_exp: %Lf, my_exp: %Lf\n", 
              x8, built_in_exp8, my_exp8);
  }
  }

  printf("-----------------SQRT--------------------\n");

  for (double x = -1.4; x < 1.4; x += 0.2) {
    printf("x: %lf\n", x);
    long double built_in_sqrt = (long double)sqrt(x);
    // long double not_my_pow = s21_pow(x, y);
    long double my_sqrt = s21_sqrt_my(x);
    // printf("base: %lf, sqrt: %lf\n", x, y);
    // printf("My pow %Lf\n", my_pow);
    // printf("NotMy pow %Lf\n", not_my_pow);
    // printf("Pow %Lf\n", built_in_pow);
    if (CHECK_INF(built_in_sqrt)) {
      if (!CHECK_INF(my_sqrt))
        printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x, built_in_sqrt, my_sqrt);
        }
    else if (!CHECK_INF(built_in_sqrt)) {
      if (CHECK_INF(my_sqrt))
        printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x, built_in_sqrt, my_sqrt);
        }
    else if (CHECK_NAN(built_in_sqrt)) {
      if (!CHECK_NAN(my_sqrt))
        printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x, built_in_sqrt, my_sqrt);
        }
    else if (!CHECK_NAN(built_in_sqrt)) {
      if (CHECK_NAN(my_sqrt))
        printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x, built_in_sqrt, my_sqrt);
        }
    else {
      if ((built_in_sqrt - my_sqrt) > EPS_for_tests) {
              printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", 
                  x, built_in_sqrt, my_sqrt);
    }
    }
  }

  // **************************************************
  double x9 = NaN;
  printf("x: %lf\n", x9);
  // **************************************************
  long double built_in_sqrt9 = (long double)sqrt(x9);
  // long double not_my_pow2 = s21_pow(x2, y2);
  long double my_sqrt9 = s21_sqrt_my(x9);
  // printf("My sqrt %Lf\n", my_sqrt2);
  // printf("NotMy sqrt %Lf\n", not_my_sqrt1);
  // printf("sqrt %Lf\n", built_in_sqrt2);
  if (CHECK_INF(built_in_sqrt9)) {
    if (!CHECK_INF(my_sqrt9))
    printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x9, built_in_sqrt9, my_sqrt9);
  }
  else if (!CHECK_INF(built_in_sqrt9)) {
    if (CHECK_INF(my_sqrt9))
    printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x9, built_in_sqrt9, my_sqrt9);  }
  else if (CHECK_NAN(built_in_sqrt9)) {
    if (!CHECK_NAN(my_sqrt9))
    printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x9, built_in_sqrt9, my_sqrt9);
  }
  else if (!CHECK_NAN(built_in_sqrt9)) {
    if (CHECK_NAN(my_sqrt9))
    printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x9, built_in_sqrt9, my_sqrt9);
  }
  else {
    if ((built_in_sqrt9 - my_sqrt9) > EPS_for_tests) {
          printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", 
              x9, built_in_sqrt9, my_sqrt9);
  }
  }

  // **************************************************
  double x10 = INF;
  printf("x: %lf\n", x10);
  // **************************************************
  long double built_in_sqrt10 = (long double)sqrt(x10);
  // long double not_my_pow2 = s21_pow(x2, y2);
  long double my_sqrt10 = s21_sqrt_my(x10);
  // printf("My sqrt %Lf\n", my_sqrt2);
  // printf("NotMy sqrt %Lf\n", not_my_sqrt1);
  // printf("sqrt %Lf\n", built_in_sqrt2);
  if (CHECK_INF(built_in_sqrt10)) {
    if (!CHECK_INF(my_sqrt10))
    printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x10, built_in_sqrt10, my_sqrt10);
  }
  else if (!CHECK_INF(built_in_sqrt10)) {
    if (CHECK_INF(my_sqrt10))
    printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x10, built_in_sqrt10, my_sqrt10);  }
  else if (CHECK_NAN(built_in_sqrt10)) {
    if (!CHECK_NAN(my_sqrt10))
    printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x10, built_in_sqrt10, my_sqrt10);
  }
  else if (!CHECK_NAN(built_in_sqrt10)) {
    if (CHECK_NAN(my_sqrt10))
    printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", x10, built_in_sqrt10, my_sqrt10);
  }
  else {
    if ((built_in_sqrt10 - my_sqrt10) > EPS_for_tests) {
          printf("%lf - FAIL - built_in_sqrt: %Lf, my_sqrt: %Lf\n", 
              x10, built_in_sqrt10, my_sqrt10);

  
    }
  }
  return 0;
}
