#include "headers/credit.h"

CreditOutput creditCalculator(CreditInput input) {
  CreditOutput output = initCreditOutput();
  if (input.yearly) {
    input.term *= 12;
  }
  if (input.annuity == 1) {
    output.annuity = 1;
    annuityCalc(input, &output);
  } else {
    diffCalc(input, &output);
  }
  return output;
}

int leapYear(int year) {
  int res = 0;
  if (year % 400 == 0) {
    res = 1;
  } else if (year % 4 == 0 && year % 100 != 0) {
    res = 1;
  }
  return res;
}

void countDays(int year, int month, int *days_month, int *days_year) {
  const int thirty_one[] = {1, 3, 5, 7, 8, 10, 12};
  for (int i = 0; i < 7; i++) {
    if (thirty_one[i] == month) {
      *days_month = 31;
      break;
    }
  }
  int leap = leapYear(year);
  if (leap) {
    *days_year = 366;
  }
  if (month == 2) {
    if (leapYear(year)) {
      *days_month = 29;
    } else {
      *days_month = 28;
    }
  }
}

void annuityCalc(CreditInput input, CreditOutput *output) {
  double monthly_rate = input.interest / 100.0 / 12.0;
  double remain_loan = (double)input.total_loan;
  double coeff = monthly_rate / (1 - pow(1 + monthly_rate, input.term * -1));
  output->max_monthly = (double)input.total_loan * coeff;
  output->max_monthly = round(output->max_monthly * 100.0f) / 100.0f;
  for (int i = 0; i < input.term; i++) {
    double temp = output->max_monthly - (remain_loan * monthly_rate);
    temp = round(temp * 100.0f) / 100.0f;
    remain_loan -= temp;
  }
  output->min_monthly = output->max_monthly;
  output->total_credit = output->max_monthly * input.term + remain_loan;
  output->overpay = output->total_credit - (double)input.total_loan;
}

void diffCalc(CreditInput input, CreditOutput *output) {
  double *payments_list = calloc(input.term, sizeof(double));
  double remain_loan = (double)input.total_loan;
  input.interest /= 100;
  for (int i = 0; i < input.term; i++) {
    int days_month = 30, days_year = 365;
    countDays(input.curr_year, input.curr_month, &days_month, &days_year);
    payments_list[i] = ((double)input.total_loan / input.term) +
                       (remain_loan * input.interest * days_month) / days_year;
    payments_list[i] = round(payments_list[i] * 100.0f) / 100.0f;
    output->total_credit += payments_list[i];
    remain_loan -=
        round(((double)input.total_loan / input.term) * 100.0f) / 100.0f;
    if (input.curr_month == 12) {
      input.curr_month = 1;
      input.curr_year++;
    } else {
      input.curr_month++;
    }
  }
  payments_list[input.term - 1] += remain_loan;
  output->max_monthly = payments_list[0];
  output->min_monthly = payments_list[0];
  for (int i = 1; i < input.term; i++) {
    if (payments_list[i] > output->max_monthly) {
      output->max_monthly = payments_list[i];
    }
    if (payments_list[i] < output->min_monthly) {
      output->min_monthly = payments_list[i];
    }
  }
  free(payments_list);
  output->overpay = output->total_credit - (double)input.total_loan;
}

CreditOutput initCreditOutput() {
  CreditOutput output = {0};
  output.annuity = 0;
  output.min_monthly = 0.0f;
  output.max_monthly = 0.0f;
  output.overpay = 0.0f;
  output.total_credit = 0.0f;
  return output;
}
