#ifndef SRC_TESTS_TEST_H_
#define SRC_TESTS_TEST_H_

#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../SmartCalcV1/back/headers/calculator.h"
#include "../SmartCalcV1/back/headers/credit.h"

#define EPS_FOR_TEST 1e-7

Suite *test_simple_operations_suite(void);
Suite *test_trigonometry_suite(void);
Suite *test_sqrt_log_suite(void);
Suite *test_calc_with_x_suite(void);
Suite *test_hard_equations_suite(void);

#endif // SRC_TESTS_TEST_H_
