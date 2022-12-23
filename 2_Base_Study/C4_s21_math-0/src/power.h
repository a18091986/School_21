#ifndef SRC_POWER_H_21_is_inf
#define SRC_POWER_H_

#include <math.h>
#include <stdio.h>

#define NaN (__builtin_nansf(""))
#define INF (__builtin_inff())
#define CHECK_NAN(x) __builtin_isnan(x)
#define CHECK_INF(x) __builtin_isinf(x)
#define S21_E 2.71828182845904523536
#define EPS 1E-15
#define EPS_for_tests 1E-8

long double s21_pow(double base, double exp);
long double s21_pow_my(double base, double exp);
long double s21_exp(double x);
long double s21_exp_my(double x);
long double s21_log(double x);
long double s21_log_my(double x);
long double s21_sqrt(double x);
long double s21_sqrt_my(double x);

long double s21_pow_my(double base, double exp) {
  long double res;

  if (base == 1.0 || exp == 0.0) {
    res = 1.0;
  } else if (base == 0 && exp < 0.0) {
    res = INF;
  } else if (base < -1.0 && CHECK_INF(exp) ) {
    res = INF;
  } else if (base > 1.0 && CHECK_INF(exp) ) {
    res = INF;
  } else if (CHECK_INF(base) && exp > 0) {
    res = INF;
  } else if (base < 0.0 && fmod(exp, 1.0) != 0) {
    res = (-1) *
          NaN;  // возведение отрицательного числа в вещественную степень
  } else if (base < 0.0 && fmod(exp, 2.0) != 0) {
    res = (-1) * s21_exp(exp * s21_log(fabs(base)));
  } else {
    res = s21_exp(exp * s21_log(fabs(base)));
  }
  return res;
}

long double s21_log(double x) {
  int ex_pow = 0;
  double result = 0;
  double compare = 0;

  if (CHECK_INF(x) || CHECK_NAN(x)) {
    result = x;
  } else if (x == 0.0) {
    result = -INF;
  } else if (x < 0.0) {
    result = NAN;
  } else if (x == 1.0) {
    result = 0.0;
  } else {
    for (; x >= S21_E; x /= S21_E, ex_pow++) continue;
    for (int i = 0; i < 100; i++) {
      compare = result;
      result = compare + 2 * (x - s21_exp(compare)) / (x + s21_exp(compare));
    }
  }
  return (result + ex_pow);
}

long double s21_log_my(double x) {
  long double result = 0.0;
  if (CHECK_INF(x))
    result = INF;
  else {
    long double y = x / (x - 1);
    long double temp_y = 1;
    for (int i = 1; i < 100; i++) {
      temp_y *= y;
      result += 1 / (temp_y * i);
    }
  }
  return result;
  //   int ex_pow = 0;
  //   double result = 0;
  //   double compare = 0;

  //   if (CHECK_INF(x) || CHECK_NAN(x)) {
  //     result = x;
  //   } else if (x == 0.0) {
  //     result = -INF;
  //   } else if (x < 0.0) {
  //     result = NaN;
  //   } else if (x == 1.0) {
  //     result = 0.0;
  //   } else {
  //     for (; x >= S21_E; x /= S21_E, ex_pow++) continue;
  //     for (int i = 0; i < 100; i++) {
  //       compare = result;
  //       result = compare + 2 * (x - s21_exp(compare)) / (x +
  //       s21_exp(compare));
  //     }
  //   }
  //   return (result + ex_pow);
}

long double s21_exp(double x) {
  int minus = 0;
  long double sum = 1.0;
  long int n = 1;

  if (x < 0) {
    x *= -1;
    minus = 1;
  }
  long double x1 = x;
  long double x2 = x * x / 2;
  do {
    sum += x1 + x2;
    n++;
    x1 *= x * x / ((2 * n - 1) * (2 * n - 2));
    x2 *= x * x / ((2 * n - 1) * 2 * n);
  } while (n < 100000);
  if (minus) sum = 1 / sum;
  return sum;
}

long double s21_exp_my(double x) {
  long double sum = 1;
  long double temp_x = 1;
  double fact = 1;

  for (int i = 1; i < 100; i++) {
    fact *= i;
    temp_x *= x;
    sum += temp_x / fact;
  }
  return sum;
}

long double s21_sqrt(double x) {
  if (CHECK_NAN(x) || CHECK_INF(x)) {
    return x;
  }
  if (x < 0) {
    return NaN;
  }

  double start = 0.0, mid, last = x;
  if (x < 1.0) {
    last = 1.0;
  }
  mid = (start + last) / 2.0;
  do {
    if (mid * mid > x) {
      last = mid;
    } else {
      start = mid;
    }
    mid = (start + last) / 2.0;
  } while ((mid - start) > 0.00000001);
  return mid;
}

long double s21_sqrt_my(double x) {
  if (CHECK_NAN(x) || CHECK_INF(x)) {
    return x;
  }
  if (x < 0) {
    return NaN;
  }

  double left = 0.0, mid, right = x;
  right = (x < 1.0) ? 1.0 : x;
  mid = left + (right - left) / 2;
  do {
    if (mid * mid > x)
      right = mid;
    else
      left = mid;
    mid = left + (right - left) / 2;
  } while ((right - left) > 0.00000001);
  return left;
}

#endif  //  SRC_POWER_H_