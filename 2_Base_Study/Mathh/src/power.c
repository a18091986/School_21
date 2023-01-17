#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double res;
  if (base == 1.0 || exp == 0.0) {
    res = 1.0;
  } else if (base == -INF && exp > 0.0) {
    res = -INF;
  } else if (base == 0.0 && exp < 0.0) {
    res = INF;
  } else if (base == 0.0 && exp >= 0.0) {
    res = 0.0;
  } else if (base < -1.0 && CHECK_INF(exp)) {
    res = INF;
  } else if (base > 1.0 && CHECK_INF(exp)) {
    res = INF;
  } else if (CHECK_INF(base) && exp > 1.0) {
    res = INF;
  } else if (CHECK_INF(base) && exp < 0.0) {
    res = 0.0;
  } else if ((base > 0) && (base < 1) && CHECK_INF(exp)) {
    res = 0.0;
  } else if (base < 0.0 && s21_fmod(exp, 1.0) != 0) {
    res = (-1) * NaN;
  } else if (base < 0.0 && s21_fmod(exp, 2.0) != 0) {
    res = (-1) * s21_exp(exp * s21_log(s21_fabs(base)));
  } else {
    res = s21_exp(exp * s21_log(s21_fabs(base)));
  }
  return res;
}

long double s21_log(double x) {
  long double result = 0, temp = 0;
  int iter = 0;
  if (x == -INF)
    result = NaN;
  else if (CHECK_INF(x))
    result = INF;
  else if (CHECK_NAN(x))
    result = NaN;
  else if (x == 0)
    result = (-1) * INF;
  else if (x < 0)
    result = NaN;
  else {
    for (; x >= S21_E; iter++) x /= S21_E;
    for (int i = 0; i < 100; i++) {
      temp = result;
      result = temp + 2 * (x - s21_exp(temp)) / (x + s21_exp(temp));
    }
    result += iter;
  }
  return result;
}

long double s21_exp(double x) {
  int below_zero = 0;
  long double result = 1;
  if (x == -INF)
    result = 0;
  else if (CHECK_INF(x))
    result = INF;
  else {
    if (x < 0) {
      x *= -1;
      below_zero = 1;
    }
    long double temp_x = 1;
    double fact = 1;
    int i = 1;
    while ((temp_x / fact) > EPS) {
      fact *= i;
      temp_x *= x;
      result += temp_x / fact;
      i++;
    }
    if (below_zero) result = 1 / result;
  }
  return result;
}

long double s21_sqrt(double x) {
  long double result;
  if (CHECK_NAN(x) || x == (-1) * INF || x < 0)
    result = NaN;
  else if (x == INF)
    result = INF;
  else {
    double left = 0.0, mid, right = x;
    right = (x < 1.0) ? 1.0 : x;
    mid = left + (right - left) / 2;
    do {
      if (mid * mid > x)
        right = mid;
      else
        left = mid;
      mid = left + (right - left) / 2;
    } while ((mid - left) > EPS * 10);
    result = left;
  }
  return result;
}
