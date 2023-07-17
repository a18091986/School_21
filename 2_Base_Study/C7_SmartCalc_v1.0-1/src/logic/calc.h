#include <math.h>

#include "logic/queue.h"
#include "logic/stack.h"
#include "main.h"

#ifndef CALC_H
#define CALC_H

double calc(queue* q, StackElement* s, double x);
double back_process(char input_string[], char polish_string[], double x,
                    queue* q_in, queue* q_polish, StackElement* s_in,
                    StackElement* s_pol, int* err);

#endif