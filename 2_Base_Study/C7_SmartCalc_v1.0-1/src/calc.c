#include <math.h>
#include "stack.h"

#define SUCCESS 1;
#define FAILURE 0;


double calc(queue * q, StackElement * s, double x, int *code_error) {
  double res = 0.0;
  int code = SUCCESS;
  *code_error = SUCCESS;
  double value;
  node lexema;
  while (get_from_queue(q, lexema.value, lexema.type)) {
    char operator[20] = lexema.value;
    char type[10] = lexema.type;

    if (!strcmp(type, "operand")) {
        s = pushStackElement(s);
        s->value = atof(operator);
        
    }
    else {
        double first = s->value;
        s = popStackElement;
        if (!strcmp(operator, "sin")) {
            pushStackElement(s);
            s->value = sin(first);
        }        
        // else if     !strcmp(operator, "cos") || 
        //     !strcmp(operator, "asin") || !strcmp(operator, "acos") || 
        //     !strcmp(operator, "tan") || !strcmp(operator, "atan") ||
        //     !strcmp(operator, "ln") || !strcmp(operator, "log") || 
        //     !strcmp(operator, "u_plus") || !strcmp(operator, "u_minus") ||
        //     !strcmp(operator, "sqrt"))) {
        //         pr
        // }
        
        else {
            if 
        }

    }
    printf("value: %s, type: %s\n", lexema.value, lexema.type);
  }
//     if (op == VALUE) {
//       code = push(&temp, VALUE, value);
//     } else if (op == X) {
//       code = push(&temp, VALUE, x);
//     } else {
//       double fir;
//       Token remove;
//       if (temp != NULL) {
//         code = pop(&temp, &remove, &fir);
//         if (code == SUCCESS) {
//           code = produce_un(&temp, fir, op);
//         }
//       } else {
//         code = FAILURE;
//       }
//       if (code == FAILURE && temp != NULL) {
//         double sec;
//         code = pop(&temp, &remove, &sec);
//         if (code == SUCCESS) {
//           code = produce_bin(&temp, fir, sec, op);
//         }
//       }
//     }
//     if (code != FAILURE) {
//       code = get(&func, &op, &value);
//     }
//   }
//   double res = 0;
//   if (temp == NULL || code == FAILURE) {
//     free_stack(&temp);
//     *code_error = FAILURE;
//   } else {
//     Token remove;
//     code = pop(&temp, &remove, &res);
//     if (code != SUCCESS) {
//       *code_error = FAILURE;
//     }
//   }

  return res;

}