#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define NaN (__builtin_nansf(""))
#define INF (__builtin_inff())
#define CHECK_NAN(x) __builtin_isnan(x)
#define CHECK_INF(x) __builtin_isinf(x)

#define EPS 0.1E-15
#define EPS_for_tests 1E-8
#define S21_PI 3.14159265358979323846
#define S21_E 2.71828182845904523536

// arithmetic
int s21_abs(int x);
long double s21_fabs(double x);
long double s21_fabsl(long double x);
long double s21_ceil(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);

// power
long double s21_pow(double base, double exp);
long double s21_exp(double x);
long double s21_log(double x);
long double s21_sqrt(double x);

// trigonometry
long double s21_sin(double x);
long double s21_cos(double x);
long double s21_tan(double x);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);

#endif  //  SRC_S21_MATH_H_
