#include "s21_math.h"

long double s21_sin(double x) {
  long double sum = 0.0;

  if (CHECK_INF(x) || CHECK_NAN(x)) {
    sum = NaN;
  } else {
    if (s21_fabs(x) > 2.0 * S21_PI) {
      if (x > 0.0) x = s21_fmod(s21_fabs(x), 2.0 * S21_PI);
      if (x < 0.0) x = -s21_fmod(s21_fabs(x), 2.0 * S21_PI);
    }

    int n = 0;
    long double cn = x;
    sum = cn;

    if (x == 0.0) {
      sum = 0.0;
    } else {
      while (s21_fabsl(cn) > EPS) {
        int k = 4 * n * n + 10 * n + 6;
        cn *= -(x * x) / k;
        sum += cn;
        n++;
      }
    }
  }
  return sum;
}

long double s21_cos(double x) {
  long double sum = 1.0;

  if (CHECK_INF(x) || CHECK_NAN(x)) {
    sum = NaN;
  } else {
    if (s21_fabs(x) > (2.0 * S21_PI)) {
      double q = s21_fmod(s21_fabs(x), 2.0 * S21_PI);
      if (x > 0.0) x = q;
      if (x < 0.0) x = -q;
    }

    int n = 1;
    long double cn = 1.0;

    while (s21_fabsl(cn) > EPS) {
      int k = 4 * n * n - 2 * n;
      cn *= -(x * x) / k;
      sum += cn;
      n++;
    }
  }

  return sum;
}

long double s21_tan(double x) {
  long double result = 0.0;

  if (CHECK_INF(x) || CHECK_NAN(x))
    result = NaN;
  else
    result = s21_sin(x) / s21_cos(x);

  return result;
}

long double s21_atan(double x) {
  int flag = 0;
  long double sum = 0.0;

  if (CHECK_NAN(x)) {
    flag++;
    sum = NaN;
  }

  if (x == -INF) {
    flag++;
    sum = S21_PI / -2.0;
  }

  if (x == INF) {
    flag++;
    sum = S21_PI / 2.0;
  }

  if (!flag) {
    if (x == 1.0) {
      flag++;
      sum = S21_PI / 4.0;
    }
    if (x == -1.0) {
      flag++;
      sum = S21_PI / -4.0;
    }
  }

  if (!flag) {
    long double xt = x;
    if (s21_fabs(x) > 1.0) xt = 1.0 / x;

    int n = 1;
    long double cn = xt;
    sum = cn;

    while (s21_fabsl(cn) > 0.1E-7) {
      cn *= -xt * xt * (2.0 * n - 1.0) / (2.0 * n + 1.0);
      sum += cn;
      n++;
    }
    if (x > 1.0) sum = S21_PI / 2.0 - sum;
    if (x < -1.0) sum = -1.0 * (S21_PI / 2.0 + sum);
  }

  return sum;
}

long double s21_asin(double x) {
  int flag = 0;
  long double result = 0.0;

  if (CHECK_INF(x) || CHECK_NAN(x)) {
    flag++;
    result = NaN;
  }

  if (!flag) {
    if (x == 1.0) {
      flag++;
      result = S21_PI / 2.0;
    }

    if (x == -1) {
      flag++;
      result = S21_PI / -2.0;
    }
  }

  if (!flag) {
    if (x > -1.0 && x < 1.0) {
      result = s21_atan(x / s21_sqrt(1.0 - x * x));
    } else {
      result = NaN;
    }
  }

  return result;
}

long double s21_acos(double x) {
  long double result = 0.0;

  if (CHECK_INF(x) || CHECK_NAN(x)) {
    result = NaN;
  } else {
    if (x >= -1.0 && x <= 1.0)
      result = S21_PI / 2.0 - s21_asin(x);
    else
      result = NaN;
  }

  return result;
}