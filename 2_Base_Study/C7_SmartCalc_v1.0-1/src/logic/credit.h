#ifndef SRC_CREDIT_H_
#define SRC_CREDIT_H_

#include "deposit.h"

int credit(char* credit, char* time, char* credit_pct, int type,
           double* pay_month_f, double* pay_month_l, double* over_pay,
           double* sum_pay);
// type 0 - ann, 1 - diff

#endif  // SRC_CREDIT_H_