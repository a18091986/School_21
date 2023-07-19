#ifndef SRC_DEPOSIT_H_
#define SRC_DEPOSIT_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int deposit(char* start, char* time, char* dep_pct, char* tax_pct,
            int pay_period, int cap, char* plus_period, char* plus_sum,
            char* minus_period, char* minus_sum, double* depo_result_sum_num,
            double* depo_result_pct_num, double* depo_result_tax_num);

// pay period 1 - month, 0 - day
// cap - 1 - yes 0 - no

int get_num(char input_number[]);
int check_correct_input(char input_number[]);

#endif  // SRC_DEPOSIT_H_