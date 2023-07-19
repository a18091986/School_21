#include "credit.h"

int credit(char* credit, char* time, char* credit_pct, int type,
           double* pay_month_f, double* pay_month_l, double* over_pay,
           double* sum_pay) {
  int err = 0;
  printf("credit: %s\n", credit);
  printf("time: %s\n", time);
  printf("credit_pct: %s\n", credit_pct);

  if (!get_num(credit) && !get_num(time) && !get_num(credit_pct) &&
      check_correct_input(credit) && check_correct_input(time) &&
      check_correct_input(credit_pct)) {
    double credit_n = atof(credit);
    double time_n = atof(time);
    double credit_pct_n = atof(credit_pct);
    // формулы с
    // https://www.pochtabank.ru/articles/kak-rasschitat-protsenty-po-kreditu
    // https://maritimebank.com/blog/rko/differentsirovannye-platezhi-po-kreditu-chto-eto-takoe-vidy-i-osobennosti-formula-rascheta/?utm_source=google.ru&utm_medium=organic&utm_campaign=google.ru&utm_referrer=google.ru#block4
    // https://www.sravni.ru/kredity/kalkuljator/
    double p = credit_pct_n /
               (12.0 * 100.0);  // сотая часть месячной процентной ставки
    if (type) {
      *pay_month_f = *pay_month_l =
          credit_n * (p + p / (pow(1 + p, time_n) - 1));
      *sum_pay = *pay_month_f * time_n;

    } else {
      double payment = 0;
      double body = credit_n / time_n;
      double current_overpay = 0;
      double credit_rest = credit_n;
      for (int i = 0; i < time_n; i++) {
        current_overpay = body * i;
        credit_rest = credit_n - current_overpay;
        payment = body + credit_rest * p;
        *sum_pay += payment;
        if (i == 0) *pay_month_f = payment;
        if (i == time_n - 1) *pay_month_l = payment;
      }
    }
    *over_pay = *sum_pay - credit_n;

  } else {
    err = 1;
  }
  return err;
}