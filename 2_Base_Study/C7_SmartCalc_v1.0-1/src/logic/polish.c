#include "logic/polish.h"

int get_prior(char* operator) {
  int prior = 0;
  if (!strcmp(operator, "+") || !strcmp(operator, "-")) {
    prior = 1;
  } else if (!strcmp(operator, "*") || !strcmp(operator, "/") ||
             !strcmp(operator, "mod")) {
    prior = 2;
  } else if (!strcmp(operator, "^")) {
    prior = 3;
  } else if (!strcmp(operator, "sin") || !strcmp(operator, "cos") ||
             !strcmp(operator, "asin") || !strcmp(operator, "acos") ||
             !strcmp(operator, "tan") || !strcmp(operator, "atan") ||
             !strcmp(operator, "ln") || !strcmp(operator, "log") ||
             !strcmp(operator, "u_plus") || !strcmp(operator, "u_minus") ||
             !strcmp(operator, "sqrt")) {
    prior = 4;
  }
  return prior;
}

int form_polish_string(queue* q, StackElement* s, char postfix[]) {
  // printf("----------------------------------------------\npolish\n");
  int res = 1;
  int j = 0;  // outer_string_pointer
  node tmp;

  while (get_from_queue(q, tmp.value, tmp.type)) {
    // printf("Sym: %s\n", tmp.value);
    if (strcmp(tmp.type, "operand") == 0) {
      // printf("Operand: %s\n", tmp.value);
      strncpy(&postfix[j], tmp.value, strlen(tmp.value));
      j += strlen(tmp.value);
      // strncpy(&postfix[j++], " ", 1);
      strcat(postfix, " ");
      j++;
    } else if (strcmp(tmp.value, ")") == 0) {
      // show_stack(s);
      if (s) {
        char current_operator_from_stack[512] = {'\0'};
        strcpy(current_operator_from_stack, s->name);
        while (strcmp(current_operator_from_stack, "(") != 0 && res) {
          // printf("Current operator from stack: %s\n",
          // current_operator_from_stack);
          strcpy(&postfix[j], current_operator_from_stack);
          j += strlen(current_operator_from_stack);
          // strncpy(&postfix[j++], " ", 1);
          strcat(postfix, " ");
          j++;
          s = popStackElement(s);
          if (s)
            strcpy(current_operator_from_stack, s->name);
          else {
            res = 0;
          }
        }
        if (strcmp(current_operator_from_stack, "(") == 0)
          s = popStackElement(s);
        else
          res = 0;
      } else {
        res = 0;
      }
    } else if (strcmp(tmp.value, "(") == 0 || strcmp(tmp.value, "sqrt") == 0 ||
               strcmp(tmp.value, "u_plus") == 0 ||
               strcmp(tmp.value, "u_minus") == 0 ||
               strcmp(tmp.value, "cos") == 0 ||
               strcmp(tmp.value, "acos") == 0 ||
               strcmp(tmp.value, "sin") == 0 ||
               strcmp(tmp.value, "asin") == 0 ||
               strcmp(tmp.value, "tan") == 0 ||
               strcmp(tmp.value, "atan") == 0 ||
               strcmp(tmp.value, "log") == 0 || strcmp(tmp.value, "ln") == 0) {
      // printf("Operator: %s\n", tmp.value);
      s = pushStackElement(s);
      setStackElementName(s, tmp.value);
      setStackElementData(s, &tmp, sizeof(tmp));
    } else if (strcmp(tmp.value, "+") == 0 || strcmp(tmp.value, "-") == 0 ||
               strcmp(tmp.value, "/") == 0 || strcmp(tmp.value, "*") == 0 ||
               strcmp(tmp.value, "mod") == 0 || strcmp(tmp.value, "^") == 0) {
      // printf("Operator: %s\n", tmp.value);
      while (s && get_prior(tmp.value) <= get_prior(s->data->value) &&
             strcmp(s->data->value, "(") != 0) {
        char current_operator_from_stack[512];
        strcpy(current_operator_from_stack, s->name);
        strcpy(&postfix[j], current_operator_from_stack);
        j += strlen(current_operator_from_stack);
        // strncpy(&postfix[j++], " ", 1);
        strcat(postfix, " ");
        j++;
        s = popStackElement(s);
      }
      s = pushStackElement(s);
      setStackElementName(s, tmp.value);
      setStackElementData(s, &tmp, sizeof(tmp));
    }
  }
  while (s) {
    char current_operator_from_stack[512];
    strcpy(current_operator_from_stack, s->name);
    strcpy(&postfix[j], current_operator_from_stack);
    j += strlen(current_operator_from_stack);
    // strncpy(&postfix[j++], " ", 1);
    strcat(postfix, " ");
    j++;
    s = popStackElement(s);
    if (strcmp(current_operator_from_stack, "(") == 0) res = 0;
  }
  // show_stack(s);
  // printf("POSTFIX_STRING: %s\n", postfix);
  // printf("polish\n----------------------------------------------\n");
  return res;
}