/**
 * @file parser.h
 * @brief Contains functions for parsing input values.
 */
#ifndef SRC_SMARTCALCV1_BACK_HEADERS_PARSER_H_
#define SRC_SMARTCALCV1_BACK_HEADERS_PARSER_H_

#include "stack.h" /**< Necessary operations for stack operations. */

/**
 * @brief Converts an input string to a stack of tokens.
 *
 * This function converts an input string to a stack of tokens according to the
 * following rules:
 * - Numbers are parsed using the parseNumber function and added to the stack.
 * - Brackets are parsed using the bracketsParsing function and added to the
 * stack.
 * - Signs are added to the stack as is, except for the '-' sign at the
 * beginning of an expression, which is replaced with the '~' sign.
 * - Trigonometric functions are parsed using the parseTrigonometry function and
 * added to the stack.
 *
 * @param src A string containing the input expression.
 * @param input A pointer to the input stack.
 * @return 1 if the input expression is valid and has been converted to a stack,
 * 0 otherwise.
 */
int convertInput(const char *src, Stack *input);

/**
 * @brief Validates and sets the value of the x parameter in the input stack.
 *
 * This function validates the input x value and sets it in the input stack if
 * it is valid.
 *
 * @param x_input A string containing the input x value.
 * @param input A pointer to the input stack.
 * @return 1 if the x value is valid and has been set in the input stack, 0
 * otherwise.
 */
int inputX(char *x_input, Stack *input);

/**
 * @brief Validates a string as a valid x value.
 *
 * This function validates a string as a valid x value according to the
 * following rules:
 * - The string can contain digits, a decimal point, the letter 'e', and the
 * letter 'P' (for pi).
 * - The string can start with a negative sign.
 * - The string can contain at most one decimal point.
 * - The string can contain at most one occurrence of 'P' or 'e'.
 * - If the string contains 'P', it must be followed by 'i'.
 *
 * @param src A string to validate as a valid x value.
 * @return 1 if the string is a valid x value, 0 otherwise.
 */
int validateX(const char *src);

/**
 * @brief Checks the result of parsing a function and updates the current index
 * in the input string.
 *
 * This function checks the result of parsing a function and updates the current
 * index in the input string according to the following rules:
 * - If the result is '\0', the function returns 0.
 * - If the result is 'l', the current index is incremented by 1.
 * - If the result is 'S', 'T', 'C', or 'R', the current index is incremented
 * by 3.
 * - Otherwise, the current index is incremented by 2.
 *
 * @param parse_res The result of parsing a function.
 * @param i A pointer to the current index in the input string.
 * @return 1 if the result is valid, 0 otherwise.
 */
int checkParseRes(char parse_res, int *i);

/**
 * @brief Parses a bracket and updates the count of left and right brackets.
 *
 * This function parses a bracket and updates the count of left and right
 * brackets according to the following rules:
 * - If the bracket is a closing parenthesis, the count of right brackets is
 * incremented if it is less than the count of left brackets.
 * - If the bracket is an opening parenthesis, the count of left brackets is
 * incremented.
 *
 * @param bracket The bracket to parse.
 * @param left_br A pointer to the count of left brackets.
 * @param right_br A pointer to the count of right brackets.
 * @return 1 if the bracket is valid, 0 otherwise.
 */
int bracketsParsing(char bracket, int *left_br, int *right_br);

/**
 * @brief Parses a number from a string and sets it in the input stack.
 *
 * This function parses a number from a string and sets it in the input stack if
 * it is valid.
 *
 * @param src A string containing the input number.
 * @param pointer A pointer to a pointer to the output string.
 * @param i A pointer to the current index in the input string.
 * @param input A pointer to the input stack.
 * @return 1 if the number is valid and has been set in the input stack, 0
 * otherwise.
 */
int parseNumber(const char *src, char **pointer, int *i, Stack *input);

/**
 * @brief Parses a trigonometric function from a string.
 *
 * This function parses a trigonometric function from a string and returns the
 * corresponding character code.
 *
 * @param src A string containing the trigonometric function.
 * @return The character code corresponding to the trigonometric function, or
 * '\0' if the function is invalid.
 */
char parseTrigonometry(const char *src);

/**
 * @brief Validates the expression in the input stack.
 *
 * This function validates the expression in the input stack according to the
 * following rules:
 * - The expression cannot start with a binary operator or a closing
 * parenthesis.
 * - The expression cannot end with a binary operator or an opening parenthesis.
 * - There cannot be two consecutive binary operators.
 * - There cannot be a closing parenthesis after an opening parenthesis.
 * - There cannot be an opening parenthesis after a number.
 *
 * @param input A pointer to the input stack.
 * @return 1 if the expression is valid, 0 otherwise.
 */
int expressionValidation(Stack *input);

#endif  // SRC_SMARTCALCV1_BACK_HEADERS_PARSER_H_
