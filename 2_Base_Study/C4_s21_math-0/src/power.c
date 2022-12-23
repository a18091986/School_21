#include "power.h"

int main() {
  //   printf("LOG: %Lf \n", s21_log(0));
  //   printf("POW %lf \n", s21_pow(0, 55));
  //   printf("EXP: %Lf \n", s21_exp(0));
  //   printf("SQRT: %Lf \n", s21_sqrt(16));

  printf("-----------------POW--------------------\n");

  //   int x = 1, y = 50;
  //   printf("base: %d, exp: %d", x, y);
  //   printf("My pow %Lf\n", s21_pow_my(x, y));
  //   printf("NotMy pow %Lf\n", s21_pow(x, y));
  //   printf("Pow %Lf\n", (long double)pow(x, y));

  //   int x = -1, y = 0.5;
  //   printf("base: %d, exp: %d\n", x, y);
  //   printf("My pow %Lf\n", s21_pow_my(x, y));
  //   printf("NotMy pow %Lf\n", s21_pow(x, y));
  //   printf("Pow %Lf\n", (long double)pow(x, y));

  //   int x = 0, y = 0;
  //   printf("base: %d, exp: %d\n", x, y);
  //   printf("My pow %Lf\n", s21_pow_my(x, y));
  //   printf("NotMy pow %Lf\n", s21_pow(x, y));
  //   printf("Pow %Lf\n", (long double)pow(x, y));

  //   double x = -0.5, y = 3.2;
  //   printf("base: %lf, exp: %lf\n", x, y);
  //   printf("My pow %Lf\n", s21_pow_my(x, y));
  //   printf("NotMy pow %Lf\n", s21_pow(x, y));
  //   printf("Pow %Lf\n", (long double)pow(x, y));

  printf("-----------------LOG--------------------\n");

  //   int x = 2;
  //   printf("x: %d\n", x);
  //   printf("My log %Lf\n", s21_log_my(x));
  //   printf("NotMy log %Lf\n", s21_log(x));
  //   printf("Log %Lf\n", (long double)log(x));

  //   int x = -1, y = 0.5;
  //   printf("base: %d, exp: %d\n", x, y);
  //   printf("My pow %Lf\n", s21_pow_my(x, y));
  //   printf("NotMy pow %Lf\n", s21_pow(x, y));
  //   printf("Pow %Lf\n", (long double)pow(x, y));

  //   int x = 0, y = 0;
  //   printf("base: %d, exp: %d\n", x, y);
  //   printf("My pow %Lf\n", s21_pow_my(x, y));
  //   printf("NotMy pow %Lf\n", s21_pow(x, y));
  //   printf("Pow %Lf\n", (long double)pow(x, y));

  //   double x = -0.5, y = 3.2;
  //   printf("base: %lf, exp: %lf\n", x, y);
  //   printf("My pow %Lf\n", s21_pow_my(x, y));
  //   printf("NotMy pow %Lf\n", s21_pow(x, y));
  //   printf("Pow %Lf\n", (long double)pow(x, y));

  printf("-----------------EXP--------------------\n");

  //   int x = 1.0;
  //   printf("x: %d\n", x);
  //   printf("My exp %Lf\n", s21_exp_my(x));
  //   printf("NotMy exp %Lf\n", s21_exp(x));
  //   printf("EXP %Lf\n", (long double)exp(x));

  //   int x = -1.0;
  //   printf("x: %d\n", x);
  //   printf("My exp %Lf\n", s21_exp_my(x));
  //   printf("NotMy exp %Lf\n", s21_exp(x));
  //   printf("EXP %Lf\n", (long double)exp(x));

  //   int x = 0;
  //   printf("x: %d\n", x);
  //   printf("My exp %Lf\n", s21_exp_my(x));
  //   printf("NotMy exp %Lf\n", s21_exp(x));
  //   printf("EXP %Lf\n", (long double)exp(x));

  //   int x = -5.4;
  //   printf("x: %d\n", x);
  //   printf("My exp %Lf\n", s21_exp_my(x));
  //   printf("NotMy exp %Lf\n", s21_exp(x));
  //   printf("EXP %Lf\n", (long double)exp(x));

  printf("-----------------SQRT--------------------\n");

  //   long double x = 0.005;
  //   printf("x: %Lf\n", x);
  //   printf("My sqrt %Lf\n", s21_sqrt_my(x));
  //   printf("NotMy sqrt %Lf\n", s21_sqrt(x));
  //   printf("SQRT %Lf\n", (long double)sqrt(x));

  //   int x = -1.0;
  //   printf("x: %d\n", x);
  //   printf("My exp %Lf\n", s21_exp_my(x));
  //   printf("NotMy exp %Lf\n", s21_exp(x));
  //   printf("EXP %Lf\n", (long double)exp(x));

  //   int x = 0;
  //   printf("x: %d\n", x);
  //   printf("My exp %Lf\n", s21_exp_my(x));
  //   printf("NotMy exp %Lf\n", s21_exp(x));
  //   printf("EXP %Lf\n", (long double)exp(x));

  long double x = -1;
  printf("x: %Lf\n", x);
  printf("My sqrt %Lf\n", s21_sqrt_my(x));
  printf("NotMy sqrt %Lf\n", s21_sqrt(x));
  printf("SQRT %Lf\n", (long double)sqrt(x));

  return 0;
}
