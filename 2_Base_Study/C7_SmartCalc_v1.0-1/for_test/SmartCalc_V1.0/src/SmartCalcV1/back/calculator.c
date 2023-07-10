#include "headers/calculator.h"

void calculator(char *user_input, char *x_input, char *calc_out) {
  double result = 0.0f;
  Stack *input = initStack();
  if (convertInput(user_input, input)) {
    Stack *rpn = rpnConverter(input);
    reverseStack(rpn);
    if (inputX(x_input, rpn) && calculation(rpn, &result)) {
      if (fabs(result) < 1e-9) {
        result = 0.0f;
      }
      sprintf(calc_out, "%.12lf", result);
      convert_output(calc_out);
    } else {
      sprintf(calc_out, "Error");
    }
    freeStack(rpn);
  } else {
    sprintf(calc_out, "Invalid input");
  }
  freeStack(input);
}

void convert_output(char *calc_out) {
  int len = strlen(calc_out) - 1;
  if (calc_out[len] == '0') {
    int terminate = len;
    for (size_t i = len; calc_out[i] == '0' || calc_out[i] == '.'; i--) {
      terminate = i;
      if (calc_out[i] == '.') {
        break;
      }
    }
    calc_out[terminate] = '\0';
  }
}

int calculation(Stack *rpn, double *result) {
  int calc_err = 0;
  Stack *temp_stack = initStack();
  while (!isEmpty(rpn) && calc_err == 0) {
    char *pop_val = pop(rpn);
    int oper_type = checkUnoDuo(pop_val[0]);
    if (oper_type == 0) {
      push(temp_stack, pop_val);
    } else {
      char *first = pop(temp_stack);
      char buffer[32] = {0};
      double temp_calc = 0.0;
      if (oper_type == 2) {
        char *second = pop(temp_stack);
        temp_calc = calcDuo(myAtof(second, rpn), myAtof(first, rpn), pop_val[0],
                            &calc_err);
        free(second);
      } else {
        temp_calc = calcUno(myAtof(first, rpn), pop_val[0], &calc_err);
      }
      snprintf(buffer, 32, "%.20lf", temp_calc);
      push(temp_stack, buffer);
      free(first);
    }
    free(pop_val);
  }
  char *res = pop(temp_stack);
  *result = myAtof(res, rpn);
  free(res);
  freeStack(temp_stack);
  return !calc_err;
}

double myAtof(char *val, Stack *rpn) {
  double res = 0.0f;
  if (val[0] == 'x') {
    if (rpn->x_value[0] == 'P') {
      res = M_PI;
    } else if (rpn->x_value[0] == 'e') {
      res = M_E;
    } else {
      res = atof(rpn->x_value);
    }
  } else if (val[0] == 'P') {
    res = M_PI;
  } else if (val[0] == 'e') {
    res = M_E;
  } else {
    res = atof(val);
  }
  return res;
}

int checkUnoDuo(char oper) {
  int out;
  char uno[] = "SsCcTtRlL~";
  char duo[] = "+-*/%^";
  if (strchr(duo, oper) != NULL) {
    out = 2;
  } else if (strchr(uno, oper) != NULL) {
    out = 1;
  } else {
    out = 0;
  }
  return out;
}

double calcUno(double a, char oper, int *calc_err) {
  double res = 0.0;
  if (unoValidation(a, oper, calc_err)) {
    switch (oper) {
      case '~':
        res = -a;
        break;
      case 's':
        res = sin(a);
        break;
      case 'S':
        res = asin(a);
        break;
      case 'c':
        res = cos(a);
        break;
      case 'C':
        res = acos(a);
        break;
      case 't':
        res = tan(a);
        break;
      case 'T':
        res = atan(a);
        break;
      case 'R':
        res = sqrt(a);
        break;
      case 'L':
        res = log10(a);
        break;
      case 'l':
        res = log(a);
        break;
      default:
        break;
    }
  }
  return res;
}

int unoValidation(double a, char oper, int *calc_err) {
  int res = 1;
  switch (oper) {
    case 'S':
    case 'C':
      if (a < -1.0f || a > 1.0f) {
        res = 0;
        *calc_err = 1;
      }
      break;
    case 't':
      if (fabs(cos(a)) < 1e-9) {
        res = 0;
        *calc_err = 1;
      }
      break;
    case 'R':
      if (a < 0.0f) {
        res = 0;
        *calc_err = 1;
      }
      break;
    case 'L':
    case 'l':
      if (a <= 0.0f) {
        res = 0;
        *calc_err = 1;
      }
      break;
    default:
      break;
  }
  return res;
}

double calcDuo(double a, double b, char oper, int *calc_err) {
  double res = 0.0;
  switch (oper) {
    case '^':
      res = pow(a, b);
      break;
    case '+':
      res = (double)a + b;
      break;
    case '-':
      res = (double)a - b;
      break;
    case '*':
      res = (double)a * b;
      break;
    case '/':
      if (b == 0) {
        *calc_err = 1;
      } else {
        res = a / b;
      }
      break;
    case '%':
      if (b == 0) {
        *calc_err = 1;
      } else {
        res = fmod(a, b);
      }
      break;
    default:
      break;
  }
  return res;
}
