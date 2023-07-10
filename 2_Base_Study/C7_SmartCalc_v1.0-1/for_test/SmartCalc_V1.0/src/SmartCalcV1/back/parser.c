#include "headers/parser.h"

int inputX(char *x_input, Stack *input) {
  int res = 1;
  if (input->x_status == 1) {
    if (strlen(x_input) == 0) {
      res = 0;
    } else {
      res = validateX(x_input);
      if (res) {
        input->x_value = (char *)calloc(strlen(x_input) + 1, sizeof(char));
        strcpy(input->x_value, x_input);
      }
    }
  }
  return res;
}

int validateX(const char *src) {
  int res = 0;
  int i = 0;
  int dot_flag = 0;
  int num_flag = 0;
  int pi_flag = 0;
  int e_flag = 0;
  if (src[0] == '-') {
    i++;
  }
  while (strchr("0123456789.Pe", src[i]) != NULL && src[i] != '\0') {
    res = 1;
    if (src[i] == 'P' && src[i + 1] != 'i') {
      res = 0;
      break;
    }
    if (src[i] != 'P' && src[i] != 'e') {
      num_flag += 1;
    }
    if (src[i] == '.') {
      dot_flag += 1;
    }
    if (src[i] == 'P') {
      pi_flag++;
      i += 1;
    } else if (src[i] == 'e') {
      e_flag++;
    }
    i += 1;
  }
  int flag_non_digits = pi_flag + e_flag;
  int flag_condition = pi_flag > 1 || e_flag > 1 || flag_non_digits > 1;

  if (dot_flag > 1 || (flag_non_digits > 0 && num_flag > 0) || flag_condition) {
    res = 0;
  }
  return res;
}

int convertInput(const char *src, Stack *input) {
  int flag = 1;
  int left_br = 0;
  int right_br = 0;
  char temp[32] = {'\0'};
  int n = strlen(src);
  for (int i = 0; i < n && flag == 1; i++) {
    char *pointer = &temp[0];
    if (strchr(DIGITS, src[i]) != NULL) {
      flag = parseNumber(src, &pointer, &i, input);
    } else if (strchr("()", src[i]) != NULL) {
      if ((flag = bracketsParsing(src[i], &left_br, &right_br)) != 0) {
        *pointer++ = src[i];
      }
    } else if (strchr(SIGNS, src[i]) != NULL) {
      if ((src[i] == '-' || src[i] == '+') && (i == 0 || src[i - 1] == '(')) {
        if (src[i] == '-') {
          *pointer++ = '~';
        }
      } else {
        *pointer++ = src[i];
      }
    } else if (strchr(TRIGONMETRY, src[i]) != NULL) {
      char parse_res = parseTrigonometry(&src[i]);
      if ((flag = checkParseRes(parse_res, &i)) != 0) {
        *pointer++ = parse_res;
      }
    } else {
      flag = 0;
    }
    *pointer = '\0';
    if (temp[0] != '\0') {
      push(input, temp);
    }
  }
  if (left_br != right_br && flag != 0) {
    flag = 0;
  }
  if (flag == 1) {
    reverseStack(input);
    flag = expressionValidation(input);
  }
  return flag;
}

int parseNumber(const char *src, char **pointer, int *i, Stack *input) {
  int res = 1;
  int dot_flag = 0;
  int num_flag = 0;
  int x_flag = 0;
  int pi_flag = 0;
  int e_flag = 0;
  while (strchr(DIGITS, src[*i]) != NULL && src[*i] != '\0') {
    if (src[*i] == 'P' && src[*i + 1] != 'i') {
      res = 0;
      break;
    }
    if (src[*i] == 'x') {
      input->x_status = 1;
      x_flag += 1;
    } else if (src[*i] != 'P' && src[*i] != 'e') {
      num_flag += 1;
    }
    if (src[*i] == '.') {
      dot_flag += 1;
    }
    *(*pointer)++ = src[*i];
    if (src[*i] == 'P') {
      pi_flag++;
      *i += 1;
    } else if (src[*i] == 'e') {
      e_flag++;
    }
    *i += 1;
  }
  *i -= 1;
  int flag_non_digits = x_flag + pi_flag + e_flag;
  int flag_condition =
      x_flag > 1 || pi_flag > 1 || e_flag > 1 || flag_non_digits > 1;

  if (dot_flag > 1 || (flag_non_digits > 0 && num_flag > 0) || flag_condition) {
    res = 0;
  }
  return res;
}

int expressionValidation(Stack *input) {
  InputNode *temp = input->top;
  int res = 1;
  char *previous = NULL;
  char *current = peek(input);
  if (current == NULL ||
      (strchr(VALIDATION, current[0]) != NULL && current[0] != '~')) {
    res = 0;
  } else if (!isEmpty(input)) {
    input->top = input->top->next;
  }
  while (!isEmpty(input) && res == 1) {
    previous = current;
    current = peek(input);
    input->top = input->top->next;
    if (strchr(VALIDATION, previous[0]) != NULL &&
        strchr(VALIDATION, current[0]) != NULL) {
      res = 0;
    } else if (strchr(VALIDATION, previous[0]) != NULL && current[0] == ')') {
      res = 0;
    } else if (previous[0] == ')' && current[0] == '(') {
      res = 0;
    } else if (previous[0] == '(' && current[0] == ')') {
      res = 0;
    } else if (strchr(DIGITS, previous[0]) != NULL && current[0] == '(') {
      res = 0;
    } else if (strchr(DIGITS, current[0]) != NULL && previous[0] == ')') {
      res = 0;
    }
  }
  if (res == 1 && strchr(VALIDATION, current[0]) != NULL) {
    res = 0;
  }
  input->top = temp;
  return res;
}

char parseTrigonometry(const char *src) {
  char res = '\0';
  int arc_func = 0;
  if (src[0] == 'a') {
    src++;
    arc_func = 1;
  }
  if (src[0] == 's' && src[1] == 'i' && src[2] == 'n' && src[3] == '(') {
    if (arc_func) {
      res = 'S';
    } else {
      res = 's';
    }
  } else if (src[0] == 'c' && src[1] == 'o' && src[2] == 's' && src[3] == '(') {
    if (arc_func) {
      res = 'C';
    } else {
      res = 'c';
    }
  } else if (src[0] == 't' && src[1] == 'a' && src[2] == 'n' && src[3] == '(') {
    if (arc_func) {
      res = 'T';
    } else {
      res = 't';
    }
  } else if (src[0] == 's' && src[1] == 'q' && src[2] == 'r' && src[3] == 't' &&
             src[4] == '(') {
    res = 'R';
  } else if (src[0] == 'l' && src[1] == 'n' && src[2] == '(') {
    res = 'l';
  } else if (src[0] == 'l' && src[1] == 'o' && src[2] == 'g' && src[3] == '(') {
    res = 'L';
  } else if (src[0] == 'm' && src[1] == 'o' && src[2] == 'd') {
    res = '%';
  }
  return res;
}

int bracketsParsing(char bracket, int *left_br, int *right_br) {
  int res = 1;
  if (bracket == ')') {
    if (*right_br < *left_br) {
      *right_br += 1;
    } else {
      res = 0;
    }
  } else if (bracket == '(') {
    *left_br += 1;
  }
  return res;
}

int checkParseRes(char parse_res, int *i) {
  int res = 1;
  if (parse_res == '\0') {
    res = 0;
  } else if (parse_res == 'l') {
    *i += 1;
  } else if (strchr("STCR", parse_res) != NULL) {
    *i += 3;
  } else {
    *i += 2;
  }
  return res;
}
