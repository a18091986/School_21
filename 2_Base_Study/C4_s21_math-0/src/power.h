#ifndef SRC_POWER_H_
#define SRC_POWER_H_

#include <math.h>
#include <stdio.h>

#define S21_NAN (__builtin_nansf(""))
#define S21_INFINITY (__builtin_inff())
#define s21_is_nan(x) __builtin_isnan(x)
#define s21_is_inf(x) __builtin_isinf(x)
#define S21_PI 3.14159265358979323846
#define S21_E 2.71828182845904523536
// MY
// #define NAN (__builtin_nanf(""))
// #define INFINITY (__builtin_inff())
// #define CHECK_NAN(x) __builtin_isnan(x)
// #define CHECK_INF(x) __builtin_isinf(x)
//

long double s21_pow(double base, double exp);
long double s21_pow_my(double base, double exp);
long double s21_exp(double x);
long double s21_exp_my(double x);
long double s21_log(double x);
long double s21_log_my(double x);
long double s21_sqrt(double x);
long double s21_sqrt_my(double x);

long double s21_pow(double base, double exp) {
  long double res;

  if (base == 1.0 || exp == 0.0) {
    res = 1.0;
  } else if (base < 0.0 && fmod(exp, 1.0) != 0) {
    res = -S21_NAN;  // возведение отрицательного числа в вещественную степень
  } else {
    res = s21_exp(exp * s21_log(fabs(base)));
  }
  if (base < 0.0 && fmod(exp, 2.0) != 0.0) {
    res *= -1;
  }
  if (base == 0.0 && exp < 0.0) res = S21_INFINITY;
  return res;
}

long double s21_pow_my(double base, double exp) {
  long double res;

  if (base == 1.0 || exp == 0.0) {
    res = 1.0;
  } else if (base == 0 && exp < 0.0) {
    res = S21_INFINITY;
  } else if (base < 0.0 && fmod(exp, 1.0) != 0) {
    res = (-1) *
          S21_NAN;  // возведение отрицательного числа в вещественную степень
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

  if (s21_is_inf(x) || s21_is_nan(x)) {
    result = x;
  } else if (x == 0.0) {
    result = -S21_INFINITY;
  } else if (x < 0.0) {
    result = S21_NAN;
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
  long double y = x / (x - 1);
  long double sum = 0;
  long double temp_y = 1;

  for (int i = 1; i < 100; i++) {
    temp_y *= y;
    sum += 1 / (temp_y * i);
  }
  return sum;
  //   int ex_pow = 0;
  //   double result = 0;
  //   double compare = 0;

  //   if (s21_is_inf(x) || s21_is_nan(x)) {
  //     result = x;
  //   } else if (x == 0.0) {
  //     result = -S21_INFINITY;
  //   } else if (x < 0.0) {
  //     result = S21_NAN;
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
  if (s21_is_nan(x) || s21_is_inf(x)) {
    return x;
  }
  if (x < 0) {
    return S21_NAN;
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
  if (s21_is_nan(x) || s21_is_inf(x)) {
    return x;
  }
  if (x < 0) {
    return S21_NAN;
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