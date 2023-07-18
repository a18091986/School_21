#include "calc.h"

#include "main.h"

double calc(queue* q, StackElement* s, double x) {
  printf("----------------------------------------------\nCALC\n");
  double res = 0.0;
  double value;
  node lexema;
  while (get_from_queue(q, lexema.value, lexema.type)) {
    // printf("value: %s, type: %s\n", lexema.value, lexema.type);
    char operator[512];
    char type[10];

    strcpy(operator, lexema.value);
    strcpy(type, lexema.type);
    if (!strcmp(type, "operand")) {
      s = pushStackElement(s);
      if (strcmp(operator, "x") == 0)
        s->value = x;
      else
        s->value = atof(operator);
      // printf("%lf\n", s->value);
    } else {
      double first = s->value;
      s = popStackElement(s);
      if (!strcmp(operator, "sin")) {
        s = pushStackElement(s);
        s->value = sin(first);
      } else if (!strcmp(operator, "cos")) {
        s = pushStackElement(s);
        s->value = cos(first);
      } else if (!strcmp(operator, "asin")) {
        s = pushStackElement(s);
        s->value = asin(first);
      } else if (!strcmp(operator, "acos")) {
        s = pushStackElement(s);
        s->value = acos(first);
      } else if (!strcmp(operator, "tan")) {
        s = pushStackElement(s);
        s->value = tan(first);
      } else if (!strcmp(operator, "atan")) {
        s = pushStackElement(s);
        s->value = atan(first);
      } else if (!strcmp(operator, "log")) {
        s = pushStackElement(s);
        s->value = log10(first);
      } else if (!strcmp(operator, "ln")) {
        s = pushStackElement(s);
        s->value = log(first);
      } else if (!strcmp(operator, "u_minus")) {
        s = pushStackElement(s);
        s->value = (-1) * first;
      } else if (!strcmp(operator, "u_plus")) {
        s = pushStackElement(s);
        s->value = first;
      } else if (!strcmp(operator, "sqrt")) {
        s = pushStackElement(s);
        s->value = sqrt(first);
        ;
      } else {
        double second = s->value;
        s = popStackElement(s);
        if (!strcmp(operator, "+")) {
          s = pushStackElement(s);
          s->value = second + first;
        } else if (!strcmp(operator, "-")) {
          s = pushStackElement(s);
          s->value = second - first;
        } else if (!strcmp(operator, "*")) {
          s = pushStackElement(s);
          s->value = second * first;
        } else if (!strcmp(operator, "/")) {
          s = pushStackElement(s);
          s->value = second / first;
        } else if (!strcmp(operator, "mod")) {
          s = pushStackElement(s);
          s->value = fmod(second, first);
        } else if (!strcmp(operator, "^")) {
          s = pushStackElement(s);
          if (second < 0 && first < 0)
            s->value = -pow(second, first);
          else
            s->value = pow(second, first);
        }
      }
    }
  }
  //   show_stack(s);
  while (s) {
    res += s->value;
    s = popStackElement(s);
  }

  printf("CALC\n----------------------------------------------\n");
  return res;
}

double back_process(char input_string[], char polish_string[], double x,
                    queue* q_in, queue* q_polish, StackElement* s_in,
                    StackElement* s_pol, int* err) {
  double result = 0.0;

  printf("%d: \n", from_input_string_to_queue(input_string, q_in, x));
  printf("123");

  // if (from_input_string_to_queue(input_string, q_in, x)) {
  //   if (form_polish_string(q_in, s_in, polish_string)) {
  //     if (from_polish_string_to_queue(polish_string, q_polish, x)) {
  //       result = calc(q_polish, s_pol, x);
  //       printf("%lf\n", result);
  //     } else {
  //       printf("Error while polish to queue\n");
  //       *err = 1;
  //     }
  //   } else {
  //     printf("Error while convert to polish\n");
  //     *err = 1;
  //   }
  // } else {
  //   printf("Error while read input string\n");
  //   *err = 1;
  // }

  return result;
}