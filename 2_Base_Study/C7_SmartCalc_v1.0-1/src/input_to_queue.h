#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#ifndef INPUT_TO_QUEUE_H
#define INPUT_TO_QUEUE_H

int from_input_to_queue(char input_expression[256], queue result_queue, double x_val);
void pass_spaces(char input_expression[], int * i);
int check_is_sin(char input_expression[], int * i);

#endif