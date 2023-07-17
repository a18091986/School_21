#include "stack.h"
#include "queue.h"


#ifndef POLISH_H
#define POLISH_H

int form_polish_string(queue * q, StackElement * s, char postfix[]);
int get_prior(char * operator);

#endif