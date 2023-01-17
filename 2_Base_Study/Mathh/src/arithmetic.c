#include "s21_math.h"

int s21_abs(int x)  // модуль
{
  if (x < 0) x = x * -1;

  return x;
}

long double s21_fabs(double x)  // модуль с точкой
{
  if (CHECK_INF(x)) {
    x = INF;
  }

  else if (CHECK_NAN(x))
    x = NaN;

  else if (x < 0.0)
    x = (long double)x * -1.0;

  return x;
}

long double s21_fabsl(long double x) {
  if (x < 0.0) x *= -1.0;

  return x;
}

long double s21_ceil(double a) {  // округление в большую сторону
  long double x = a;

  if (x - (long long int)a > 0) {
    x = x - (x - (long long int)a) + 1;
  } else {
    x = x - (x - (long long int)a);
  }
  return x;
}

long double s21_floor(double x)  // округдение в меньшую сторону
{
  long double a = x;

  if (CHECK_INF(x)) {
    a = INF;
    if (x < 0) a = -INF;
  }

  else if (CHECK_NAN(x))
    a = NaN;

  else {
    if (a - (long long int)a > 0)
      a = a - (a - (long long int)a);
    else if (a - (long long int)a < 0)
      a = (long long int)a - 1;
  }

  return a;
}

long double s21_fmod(double x, double y)  // остаток от деления с точкой
{
  long double res;

  if ((CHECK_INF(x) || CHECK_NAN(x) || CHECK_NAN(y)))
    res = NaN;
  else if ((x == 0.0) && CHECK_INF(y))
    res = 0.0;
  else if ((x != 0.0) && CHECK_INF(y))
    res = (long double)x;
  else if (y == 0.0)
    res = NaN;
  else {
    long long int mod = 0;
    mod = x / y;
    res = (long double)x - mod * (long double)y;
  }

  return res;
}