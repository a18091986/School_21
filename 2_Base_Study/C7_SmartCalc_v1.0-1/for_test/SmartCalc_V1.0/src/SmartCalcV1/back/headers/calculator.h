/**
 * @file calculator.h
 * @brief Calculator functions for evaluating mathematical expressions.
 */
#ifndef SRC_SMARTCALCV1_BACK_HEADERS_CALCULATOR_H_
#define SRC_SMARTCALCV1_BACK_HEADERS_CALCULATOR_H_

#include "parser.h"
#include "stack.h"
/**
 * @brief Evaluates a mathematical expression and stores the result in calc_out.
 *
 * @param user_input The input mathematical expression as a string.
 * @param x_input The value of x to be used in the expression.
 * @param calc_out The output buffer to store the result of the calculation.
 */
void calculator(char *user_input, char *x_input, char *calc_out);

/**
 * @brief Converts the output of the calculation to a more readable format
 * (removes trailing zeroes).
 *
 * @param calc_out The output buffer containing the result of the calculation.
 */
void convert_output(char *calc_out);

/**
 * @brief Performs the calculation using the Reverse Polish Notation (RPN)
 * stack.
 *
 * @param rpn The RPN stack containing the input expression.
 * @param result A pointer to a double variable to store the result of the
 * calculation.
 * @return Returns 1 if the calculation is successful, 0 otherwise.
 */
int calculation(Stack *rpn, double *result);

/**
 * @brief Performs a unary operation on the given value.
 *
 * @param a The input value to perform the unary operation on.
 * @param oper The unary operator character.
 * @param calc_err A pointer to an integer variable to store any calculation
 * error.
 * @return The result of the unary operation.
 */
double calcUno(double a, char oper, int *calc_err);

/**
 * @brief Performs a binary operation on the given values.
 *
 * @param a The first input value for the binary operation.
 * @param b The second input value for the binary operation.
 * @param oper The binary operator character.
 * @param calc_err A pointer to an integer variable to store any calculation
 * error.
 * @return The result of the binary operation.
 */
double calcDuo(double a, double b, char oper, int *calc_err);

/**
 * @brief Checks if the given operator is unary or binary.
 *
 * @param oper The input operator character.
 * @return Returns 0 if not an operator, 1 if unary, and 2 if binary.
 */
int checkUnoDuo(char oper);

/**
 * @brief Validates the input value and operator for a unary operation.
 *
 * @param a The input value to perform the unary operation on.
 * @param oper The unary operator character.
 * @param calc_err A pointer to an integer variable to store any calculation
 * error.
 * @return Returns 1 if the input value and operator are valid, 0 otherwise.
 */
int unoValidation(double a, char oper, int *calc_err);

/**
 * @brief Converts a string to a double, considering special values like 'x',
 * 'e', and 'Pi'.
 *
 * @param val The input string to be converted.
 * @param rpn The RPN stack containing the input expression.
 * @return The converted double value.
 */
double myAtof(char *val, Stack *rpn);

#endif  // SRC_SMARTCALCV1_BACK_HEADERS_CALCULATOR_H_
