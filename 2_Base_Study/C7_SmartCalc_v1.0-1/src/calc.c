#include "calc.h"

#define SUCCESS 1;
#define FAILURE 0;


double calc(queue * q, StackElement * s, double x, int *code_error) {
  printf("----------------------------------------------\nCALC\n");
  double res = 0.0;
  int code = SUCCESS;
  *code_error = SUCCESS;
  double value;
  node lexema;
  while (get_from_queue(q, lexema.value, lexema.type)) {
    printf("value: %s, type: %s\n", lexema.value, lexema.type);
    char operator[20];
    char type[10];
    strcpy(operator, lexema.value);
    strcpy(type, lexema.type);

    if (!strcmp(type, "operand")) {
        printf("%lf\n", atof(operator));
        s = pushStackElement(s);
        s->value = atof(operator);
        printf("%lf\n", s->value);
    }
    else {
        double first = s->value;
        s = popStackElement(s);
        if (!strcmp(operator, "sin")) {
            pushStackElement(s);
            s->value = sin(first);
        } 
        else if (!strcmp(operator, "cos")) {
            pushStackElement(s);
            s->value = cos(first);
        }        
        else if (!strcmp(operator, "asin")) {
            pushStackElement(s);
            s->value = asin(first);
        }        
        else if (!strcmp(operator, "acos")) {
            pushStackElement(s);
            s->value = acos(first);
        }        
        else if (!strcmp(operator, "tan")) {
            pushStackElement(s);
            s->value = tan(first);
        }        
        else if (!strcmp(operator, "atan")) {
            pushStackElement(s);
            s->value = atan(first);
        }        
        else if (!strcmp(operator, "log")) {
            pushStackElement(s);
            s->value = log10(first);
        }        
        else if (!strcmp(operator, "ln")) {
            pushStackElement(s);
            s->value = log(first);
        }        
        else if (!strcmp(operator, "u_minus")) {
            pushStackElement(s);
            s->value = -first;
        }        
        else if (!strcmp(operator, "u_plus")) {
            pushStackElement(s);
            s->value = first;
        }
        else if (!strcmp(operator, "sqrt")) {
            pushStackElement(s);
            s->value = sqrt(first);;
        }               
        else {
            double second = s->value;
            s = popStackElement(s);
            if (!strcmp(operator, "+")) {
                s = pushStackElement(s);
                s->value = second + first;
            }
            else if (!strcmp(operator, "-")) {
                s = pushStackElement(s);
                s->value = second - first;
            }
            else if (!strcmp(operator, "*")) {
                s = pushStackElement(s);
                s->value = second * first;
            }
            else if (!strcmp(operator, "/")) {
                s = pushStackElement(s);
                s->value = second / first;
            }
            else if (!strcmp(operator, "mod")) {
                s = pushStackElement(s);
                s->value = fmod(second, first);
            }
            else if (!strcmp(operator, "^")) {
                s = pushStackElement(s);
                if (second < 0 && first < 0)
                    s->value = -pow(second, first);
                else
                    s->value = pow(second, first);
            }
        }
    }
  }
  show_stack(s);
  printf("CALC\n----------------------------------------------\n");
  return res;

}