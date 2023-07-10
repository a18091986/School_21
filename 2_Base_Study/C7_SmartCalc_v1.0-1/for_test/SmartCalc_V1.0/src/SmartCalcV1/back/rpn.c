#include "headers/stack.h"

Stack *rpnConverter(Stack *input) {
  Stack *rpn_stack = initStack();
  Stack *temp_stack = initStack();
  rpn_stack->x_status = input->x_status;
  if (rpn_stack->x_status == 1 && input->x_value != NULL) {
    rpn_stack->x_value =
        (char *)calloc(strlen(input->x_value) + 1, sizeof(char));
    strcpy(rpn_stack->x_value, input->x_value);
  }
  while (!isEmpty(input)) {
    char *pop_value = pop(input);
    int priority = checkPriority(pop_value[0]);
    if (priority == -1) {
      push(rpn_stack, pop_value);
    } else {
      operationHandler(rpn_stack, temp_stack, pop_value);
    }
    free(pop_value);
  }
  while (!isEmpty(temp_stack)) {
    char *pop_value = pop(temp_stack);
    push(rpn_stack, pop_value);
    free(pop_value);
  }
  freeStack(temp_stack);
  return rpn_stack;
}

void operationHandler(Stack *rpn_stack, Stack *temp_stack, char *pop_value) {
  char *peek_inside = peek(temp_stack);
  if (peek_inside != NULL) {
    if (pop_value[0] == ')') {
      char *operation = pop(temp_stack);
      while (!isEmpty(temp_stack) && operation[0] != '(') {
        push(rpn_stack, operation);
        free(operation);
        operation = pop(temp_stack);
      }
      if (operation != NULL) {
        free(operation);
      }
    } else if (pop_value[0] == '(') {
      push(temp_stack, pop_value);
    } else {
      int peek_priority = checkPriority(peek_inside[0]);
      int pop_priority = checkPriority(pop_value[0]);
      if (peek_priority < pop_priority) {
        push(temp_stack, pop_value);
      } else {
        while (priorityValidation(temp_stack, peek_priority, pop_priority)) {
          char *operation = pop(temp_stack);
          push(rpn_stack, operation);
          free(operation);
          peek_inside = peek(temp_stack);
          if (peek_inside != NULL) {
            peek_priority = checkPriority(peek_inside[0]);
          }
        }
        push(temp_stack, pop_value);
      }
    }
  } else {
    push(temp_stack, pop_value);
  }
}

int priorityValidation(Stack *temp_stack, int peek_priority, int pop_priority) {
  int res = 0;
  int empty = !isEmpty(temp_stack);
  int compare = peek_priority >= pop_priority;
  int power_case = peek_priority == 5 && pop_priority == 5;
  if (empty && compare && !(power_case)) {
    res = 1;
  }
  return res;
}

int checkPriority(char oper) {
  int out;
  if (strchr("^", oper) != NULL) {
    out = 5;
  } else if (strchr(OPERATIONS, oper) != NULL) {
    out = 4;
  } else if (strchr("~", oper) != NULL) {
    out = 3;
  } else if (strchr("*/%", oper) != NULL) {
    out = 2;
  } else if (strchr("+-", oper) != NULL) {
    out = 1;
  } else if (oper == '(' || oper == ')') {
    out = 0;
  } else {
    out = -1;
  }
  return out;
}
