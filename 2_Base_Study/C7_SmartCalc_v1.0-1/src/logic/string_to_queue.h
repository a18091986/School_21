#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logic/queue.h"
#include "main.h"

#ifndef STRING_TO_QUEUE_H
#define STRING_TO_QUEUE_H

int from_input_string_to_queue(char input_expression[], queue* result_queue,
                               double x_val);
int from_polish_string_to_queue(char input_expression[], queue* result_queue,
                                double x_val);
void pass_spaces(char const input_expression[], int* i);

//-------------------------------------------------------------------------------
//проверки на функцию
// return 0 при совпадении

int check_is_sin(char input_expression[], int* i);
int check_is_asin(char input_expression[], int* i);
int check_is_cos(char input_expression[], int* i);
int check_is_acos(char input_expression[], int* i);
int check_is_tan(char input_expression[], int* i);
int check_is_atan(char input_expression[], int* i);
int check_is_sqrt(char input_expression[], int* i);
int check_is_ln(char input_expression[], int* i);
int check_is_log(char input_expression[], int* i);
int check_is_mod(char input_expression[], int* i);
int check_is_u_minus(char input_expression[], int* i);
int check_is_u_plus(char input_expression[], int* i);

//--------------------------------------------------------------------------------
int check_plus_or_minus(char const input_expression[], int* i);
// проверка итогового знака, когда идёт несколько плюсов и минусов подряд
// return 0 => plus; 1 => minus
//--------------------------------------------------------------------------------

int get_digits(char input_expression[], int* i, char digits_string[],
               int* is_next_pow, int* is_prev_pow, int* pow_count);
int get_digits_1(char input_expression[], int* i, char digits_string[]);
// выбирает из строки все подряд идущие цифры и одну точку, если есть
// если получаемая строка цифр соответствует целому или вещественному числу:
// return 1 иначе return 0

#endif

// OPERATIONS

// (
// )
// - унарный
// + унарный
// ^
// *
// /
// mod остаток от деления
// + сложение
// - вычитание

// Функции

// sin
// asin
// tan
// atan
// cos
// acos
// sqrt
// ln - натуральный логарифм
// log - десятичный логарифм