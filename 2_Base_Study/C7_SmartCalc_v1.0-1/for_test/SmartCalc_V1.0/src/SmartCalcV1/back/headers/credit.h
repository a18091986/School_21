/**
 * @file credit.h
 * @brief Header file for credit calculator functions.
 */
#ifndef SRC_SMARTCALCV1_BACK_HEADERS_CREDIT_H_
#define SRC_SMARTCALCV1_BACK_HEADERS_CREDIT_H_

#include "includes.h" /**< Necessary header files for backend module. */

/**
 * @brief Struct containing the output of the credit calculator.
 */
typedef struct {
  int annuity; /**< Flag indicating whether the credit is annuity-based. */
  double min_monthly;  /**< Minimum monthly payment. */
  double max_monthly;  /**< Maximum monthly payment. */
  double overpay;      /**< Amount of overpayment. */
  double total_credit; /**< Total amount of credit. */
} CreditOutput;

/**
 * @brief Struct containing the input parameters for the credit calculator.
 */
typedef struct {
  int annuity;     /**< Flag indicating whether the credit is annuity-based. */
  int total_loan;  /**< Total amount of the loan. */
  int term;        /**< Term of the loan in months. */
  int yearly;      /**< Flag indicating whether the term is in years. */
  double interest; /**< Interest rate of the loan. */
  int curr_year;   /**< Current year. */
  int curr_month;  /**< Current month. */
} CreditInput;

/**
 * @brief Determines whether a given year is a leap year.
 *
 * @param year The year to check.
 * @return 1 if the year is a leap year, 0 otherwise.
 */
int leapYear(int year);

/**
 * @brief Counts the number of days in a given month and year.
 *
 * @param year The year.
 * @param month The month.
 * @param days_month Pointer to the variable that will hold the number of days
 * in the month.
 * @param days_year Pointer to the variable that will hold the number of days in
 * the year.
 */
void countDays(int year, int month, int *days_month, int *days_year);

/**
 * @brief Calculates the output of the credit calculator for an annuity-based
 * loan.
 *
 * @param input The input parameters for the credit calculator.
 * @param output Pointer to the output struct.
 */
void annuityCalc(CreditInput input, CreditOutput *output);

/**
 * @brief Calculates the output of the credit calculator for a differentiated
 * loan.
 *
 * @param input The input parameters for the credit calculator.
 * @param output Pointer to the output struct.
 */
void diffCalc(CreditInput input, CreditOutput *output);

/**
 * @brief Initializes a CreditOutput struct with default values.
 *
 * @return The initialized CreditOutput struct.
 */
CreditOutput initCreditOutput();

/**
 * @brief Calculates the output of the credit calculator based on the input
 * parameters.
 *
 * @param input The input parameters for the credit calculator.
 * @return The output of the credit calculator.
 */
CreditOutput creditCalculator(CreditInput input);

#endif  // SRC_SMARTCALCV1_BACK_HEADERS_CREDIT_H_
