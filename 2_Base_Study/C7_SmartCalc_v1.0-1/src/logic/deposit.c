#include "deposit.h"

int deposit(char* start, char* time, char* dep_pct, char* tax_pct,
            int pay_period, int cap, char* plus_period, char* plus_sum,
            char* minus_period, char* minus_sum, double* depo_result_sum_num,
            double* depo_result_pct_num, double* depo_result_tax_num) {
  //   int is_double = 0;

  // https://journal.tinkoff.ru/guide/deposit-interests/
  int err = 0;
  printf("start: %s\n", start);
  printf("time: %s\n", time);
  printf("dep_pct: %s\n", dep_pct);
  printf("tax_pct: %s\n", tax_pct);
  printf("plus_period: %s\n", plus_period);
  printf("plus_sum: %s\n", plus_sum);
  printf("minus_period: %s\n", minus_period);
  printf("minus_sum: %s\n", minus_sum);

  if (!get_num(start) && !get_num(time) && !get_num(dep_pct) &&
      !get_num(tax_pct) && !get_num(plus_period) && !get_num(plus_sum) &&
      !get_num(minus_period) && !get_num(minus_sum) &&
      check_correct_input(start) && check_correct_input(time) &&
      check_correct_input(dep_pct) && check_correct_input(tax_pct) &&
      check_correct_input(plus_period) && check_correct_input(plus_sum) &&
      check_correct_input(minus_period) && check_correct_input(minus_sum)) {
    *depo_result_sum_num = atof(start);
    double time_n = atof(time);
    double dep_pct_n = atof(dep_pct);
    double tax_pct_n = atof(tax_pct);
    double plus_period_n = atof(plus_period);
    double plus_sum_n = atof(plus_sum);
    double minus_period_n = atof(minus_period);
    double minus_sum_n = atof(minus_sum);

    double days_in_year = 365.25;
    double time_in_years = time_n * 30.5 / days_in_year;

    // количество периодов капитализации в год
    int p = cap ? (pay_period ? 12 : 365) : 1;

    // эффективная ставка
    double effect_st =
        (pow((1 + dep_pct_n / (100 * p)), time_in_years * p) - 1) * 100 /
        time_in_years;

    // printf("Эффективная ставка: %lf\n", effect_st);
    double additional_sum = 0.0;

    for (int i = 0; i < time_n; i++) {
      if (i % (int)plus_period_n == 0) {
        *depo_result_sum_num += plus_sum_n;
        additional_sum += plus_sum_n;
      }
      if (i % (int)minus_period_n == 0) {
        *depo_result_sum_num -= minus_sum_n;
        additional_sum -= minus_sum_n;
      }
      *depo_result_sum_num += *depo_result_sum_num * effect_st / 1200;
      *depo_result_pct_num =
          *depo_result_sum_num - atof(start) - additional_sum;
      *depo_result_tax_num = *depo_result_pct_num * tax_pct_n / 100;
    }

  } else {
    printf("ERROR!\n");
    err = 1;
  }

  return err;
}

int get_num(char input_number[]) {
  // получение вещественного или целого числа
  //   printf("--------------------------------------------\n");
  //   printf("string: %s\n", input_number);
  char result_number[1024] = {'\0'};
  int err = 0;
  size_t i;
  int point_count = 0;
  for (i = 0; i < strlen(input_number); i++) {
    if (strchr("-0123456789.", input_number[i])) {
      if (input_number[i] == '.') point_count++;
    }
  }
  // printf("Result_number: %s\n", result_number);
  // printf("Input_number: %s\n", input_number);
  strncpy(result_number, input_number, i);
  // printf("Result_number: %s\n", result_number);
  // printf("Input_number: %s\n", input_number);
  // //   printf("i: %ld\n", i);
  // //   printf("result_number: %s\n", result_number);
  // //   printf("input_number: %s\n", input_number);
  if (strlen(result_number) != strlen(input_number) || point_count > 1) {
    err = 1;
  }

  //   printf("from get_num \n");
  //   printf("--------------------------------------------\n");
  return err;
}

int check_correct_input(char input_number[]) {
  int right_sym = 1;
  int right_len = strlen(input_number) < 256;
  for (size_t i = 0; i < strlen(input_number); i++)
    if (!strchr("-0123456789.", input_number[i])) right_sym = 0;
  int not_empty = strcmp(input_number, "\0") ? 1 : 0;
  // printf("input: %s, right_sym: %d, right_len: %d, not_empty: %d\n",
  //        input_number, right_sym, right_len, not_empty);
  return (right_len && not_empty && right_sym);
}