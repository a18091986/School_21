#include "logic/string_to_queue.h"

int from_input_string_to_queue(char input_expression[], queue* result_queue,
                               double x_val) {
  // printf("input: %s\n", input_expression);
  int is_previous_operand = 0;  // отслеживание типа предыдущей лексемы
  int res = 1;
  int i = 0;
  int pow_count = 0;
  // printf("X: %lf\n", x_val);
  // queue_head(&result_queue);

  int length_of_ie = (int)strlen(input_expression);
  // printf("Длина входной строки: %d\n-----------------------\n",
  // length_of_ie);

  // printf(
  //     "----------------------------------------------\nfrom_input_string_to_"
  //     "queue\n");

  while (i != length_of_ie - 1) {
    // printf("Symbol: %c\n", input_expression[i]);
    if (input_expression[i] == ' ') {
      pass_spaces(input_expression, &i);
    }
    if (input_expression[i] == '.') {
      // printf("Point not in number");
      res = 0;
      i++;
    } else if (input_expression[i] == '+' || input_expression[i] == '-') {
      // printf("i: %d\n", i);
      int plus_or_minus_flag = check_plus_or_minus(input_expression, &i);
      int is_unar = is_previous_operand ? 0 : 1;
      if (is_unar) {
        if (!plus_or_minus_flag)
          res = insert_queue(result_queue, "u_plus", "operator");
        else
          res = insert_queue(result_queue, "u_minus", "operator");
      } else {
        char plus_or_minus[2] = {"/0"};
        strcpy(plus_or_minus, plus_or_minus_flag == 0 ? "+" : "-");
        res = insert_queue(result_queue, plus_or_minus, "operator");
      }
      is_previous_operand = 0;
    } else if (strchr("0123456789", input_expression[i])) {
      int is_next_pow = 0;
      int is_prev_pow = 0;
      char number[511] = {'\0'};
      if (!get_digits(input_expression, &i, number, &is_next_pow, &is_prev_pow,
                      &pow_count)) {
        // printf("Incorrect number\n");
        res = 0;
      } else {
        // printf("pow_count: %d, prev_pow: %d, next_pow: %d\n", pow_count,
        //        is_prev_pow, is_next_pow);
        if (is_next_pow && pow_count == 1) {
          res = insert_queue(result_queue, "(", "operator") &&
                insert_queue(result_queue, number, "operand");
        } else if (is_prev_pow && pow_count == 2) {
          res = insert_queue(result_queue, number, "operand") &&
                insert_queue(result_queue, ")", "operator");
          pow_count = 0;
        } else {
          res = insert_queue(result_queue, number, "operand");
        }
        is_previous_operand = 1;
      }
    } else if (input_expression[i] == 'x') {
      res = insert_queue(result_queue, "x", "operand");
      if (is_previous_operand) res = 0;
      is_previous_operand = 1;
      i++;
    } else if (input_expression[i] == '(') {
      res = insert_queue(result_queue, "(", "operator");
      is_previous_operand = 0;
      i++;
    } else if (input_expression[i] == ')') {
      res = insert_queue(result_queue, ")", "operator");
      is_previous_operand = 1;
      i++;
    } else if (input_expression[i] == '/' && is_previous_operand) {
      res = insert_queue(result_queue, "/", "operator");
      is_previous_operand = 0;
      i++;
    } else if (input_expression[i] == '*' && is_previous_operand) {
      res = insert_queue(result_queue, "*", "operator");
      is_previous_operand = 0;
      i++;
    } else if (input_expression[i] == '^' && is_previous_operand) {
      res = insert_queue(result_queue, "^", "operator");
      pow_count++;
      is_previous_operand = 0;
      i++;
    } else if (check_is_sin(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "sin", "operator");
      is_previous_operand = 0;
      i += 3;
    } else if (check_is_asin(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "asin", "operator");
      is_previous_operand = 0;
      i += 4;
    } else if (check_is_cos(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "cos", "operator");
      is_previous_operand = 0;
      i += 3;
    } else if (check_is_acos(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "acos", "operator");
      is_previous_operand = 0;
      i += 4;
    } else if (check_is_tan(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "tan", "operator");
      is_previous_operand = 0;
      i += 3;
    } else if (check_is_atan(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "atan", "operator");
      is_previous_operand = 0;
      i += 4;
    } else if (check_is_sqrt(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "sqrt", "operator");
      is_previous_operand = 0;
      i += 4;
    } else if (check_is_ln(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "ln", "operator");
      is_previous_operand = 0;
      i += 2;
    } else if (check_is_log(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "log", "operator");
      is_previous_operand = 0;
      i += 3;
    } else if (check_is_mod(input_expression, &i) == 0 && is_previous_operand) {
      res = insert_queue(result_queue, "mod", "operator");
      is_previous_operand = 0;
      i += 3;
      // break;
    } else if (check_is_u_minus(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "u_minus", "operator");
      i += 7;
    } else if (check_is_u_plus(input_expression, &i) == 0) {
      res = insert_queue(result_queue, "u_plus", "operator");
      i += 6;
    } else {
      // printf("No match in input_to_queue function\n");
      res = 0;
    }
    if (!res) {
      break;
    }
  }
  // printf(
  //     "from_input_string_to_queue\n--------------------------------------------"
  //     "\n");
  return res;
}

int from_polish_string_to_queue(char input_expression[], queue* result_queue,
                                double x_val) {
  int res = 1;
  int i = 0;
  int length_of_ie = (int)strlen(input_expression);

  // printf(
  //     "----------------------------------------------\nfrom_polish_string_to_"
  //     "queue\n");

  while (i != length_of_ie - 1) {
    if (input_expression[i] == ' ') {
      pass_spaces(input_expression, &i);
    } else if (input_expression[i] == '+') {
      res = insert_queue(result_queue, "+", "operator");
      i++;
    } else if (input_expression[i] == '-') {
      res = insert_queue(result_queue, "-", "operator");
      i++;
    } else if (strchr("0123456789", input_expression[i])) {
      char number[511] = {'\0'};
      if (!get_digits_1(input_expression, &i, number))
        res = 0;
      else
        res = insert_queue(result_queue, number, "operand");
    } else if (input_expression[i] == 'x') {
      res = insert_queue(result_queue, "x", "operand");
      i++;
    } else if (input_expression[i] == '(') {
      res = insert_queue(result_queue, "(", "operator");
      i++;
    } else if (input_expression[i] == ')') {
      res = insert_queue(result_queue, ")", "operator");
      i++;
    } else if (input_expression[i] == '/') {
      res = insert_queue(result_queue, "/", "operator");
      i++;
    } else if (input_expression[i] == '*') {
      res = insert_queue(result_queue, "*", "operator");
      i++;
    } else if (input_expression[i] == '^') {
      res = insert_queue(result_queue, "^", "operator");
      i++;
    } else if (!strncmp("sin", &input_expression[i], 3)) {
      res = insert_queue(result_queue, "sin", "operator");
      i += 3;
    } else if (!strncmp("asin", &input_expression[i], 4)) {
      res = insert_queue(result_queue, "asin", "operator");
      i += 4;
    } else if (!strncmp("cos", &input_expression[i], 3)) {
      res = insert_queue(result_queue, "cos", "operator");
      i += 3;
    } else if (!strncmp("acos", &input_expression[i], 4)) {
      res = insert_queue(result_queue, "acos", "operator");
      i += 4;
    } else if (!strncmp("tan", &input_expression[i], 3)) {
      res = insert_queue(result_queue, "tan", "operator");
      i += 3;
    } else if (!strncmp("atan", &input_expression[i], 4)) {
      res = insert_queue(result_queue, "atan", "operator");
      i += 4;
    } else if (!strncmp("sqrt", &input_expression[i], 4)) {
      res = insert_queue(result_queue, "sqrt", "operator");
      i += 4;
    } else if (!strncmp("ln", &input_expression[i], 2)) {
      res = insert_queue(result_queue, "ln", "operator");
      i += 2;
    } else if (!strncmp("log", &input_expression[i], 3)) {
      res = insert_queue(result_queue, "log", "operator");
      i += 3;
    } else if (!strncmp("mod", &input_expression[i], 3)) {
      res = insert_queue(result_queue, "mod", "operator");
      i += 3;
    } else if (!strncmp("u_minus", &input_expression[i], 7)) {
      res = insert_queue(result_queue, "u_minus", "operator");
      i += 7;
    } else if (!strncmp("u_plus", &input_expression[i], 6)) {
      res = insert_queue(result_queue, "u_plus", "operator");
      i += 6;
    } else {
      res = 0;
    }
    if (res == 0) break;
  }
  // printf(
  //     "from_polish_string_to_queue\n-----------------------------------------"
  //     "--"
  //     "---\n");
  return res;
}

void pass_spaces(char const input_expression[], int* i) {
  // пропуск пробелов
  while (input_expression[*i] == ' ') (*i)++;
}

int check_plus_or_minus(char const input_expression[], int* i) {
  // определяет итоговый знак в случае нескольких подряд +/-
  int minus_count = 0;
  int plus_count = 0;

  while ((input_expression[*i] == '+') || (input_expression[*i] == '-')) {
    if (input_expression[*i] == '-')
      minus_count++;
    else
      plus_count++;
    (*i)++;
  }
  int res = (-minus_count + plus_count) > 0 ? 0 : 1;
  return res;
}

int get_digits(char input_expression[], int* i, char digits_string[],
               int* is_next_pow, int* is_prev_pow, int* const pow_count) {
  // получение вещественного или целого числа
  int count = 0;
  int point_count = 0;
  int j = *i;
  if (input_expression[*i - 1] == '^' && *pow_count != 0) {
    *is_prev_pow = 1;
  }
  while (strchr("0123456789.", input_expression[*i])) {
    if (input_expression[*i] == '.') point_count++;
    count++;
    (*i)++;
  }
  strncpy(digits_string, &input_expression[j], count);
  pass_spaces(input_expression, i);
  if (input_expression[*i] == '^' && *pow_count != 0) {
    *is_next_pow = 1;
  }
  // printf("--------------------------------------------\n");
  // printf("from get_digits: \n");
  // printf("Result digits string: %s\n", digits_string);
  // printf("Next symbol: %c\n", input_expression[*i]);
  return point_count <= 1 ? 1 : 0;
}

int get_digits_1(char input_expression[], int* i, char digits_string[]) {
  // получение вещественного или целого числа
  int count = 0;
  int point_count = 0;
  int j = *i;
  while (strchr("0123456789.", input_expression[*i])) {
    if (input_expression[*i] == '.') point_count++;
    count++;
    (*i)++;
  }
  strncpy(digits_string, &input_expression[j], count);
  // printf("--------------------------------------------\n");
  // printf("from get_digits: \n");
  // printf("Result digits string: %s\n", digits_string);
  // printf("Next symbol: %c\n", input_expression[*i]);
  return point_count <= 1 ? 1 : 0;
}

int check_is_sin(char input_expression[], int* i) {
  char sin_string[] = "sin(\0";
  // printf("------------------------------------------\n");
  // printf("Check is sin: %s", &input_expression[*i]);
  // printf("sin_string: %s\n", sin_string);
  // printf("Strncmp: %d\n", strncmp(sin_string, &input_expression[*i], 3));
  return strncmp(sin_string, &input_expression[*i], 4);
}

int check_is_asin(char input_expression[], int* i) {
  char asin_string[] = "asin(\0";
  // printf("------------------------------------------\n");
  // printf("Check is asin: %s", &input_expression[*i]);
  // printf("asin_string: %s\n", asin_string);
  // printf("Strncmp: %d\n", strncmp(asin_string, &input_expression[*i], 5));
  return strncmp(asin_string, &input_expression[*i], 5);
}

int check_is_tan(char input_expression[], int* i) {
  char tan_string[] = "tan(\0";
  // printf("------------------------------------------\n");
  // printf("Check is tan: %s", &input_expression[*i]);
  // printf("tan_string: %s\n", tan_string);
  // printf("Strncmp: %d\n", strncmp(tan_string, &input_expression[*i], 4));
  return strncmp(tan_string, &input_expression[*i], 4);
}

int check_is_atan(char input_expression[], int* i) {
  char atan_string[] = "atan(\0";
  // printf("------------------------------------------\n");
  // printf("Check is atan: %s", &input_expression[*i]);
  // printf("atan_string: %s\n", atan_string);
  // printf("Strncmp: %d\n", strncmp(atan_string, &input_expression[*i], 5));
  return strncmp(atan_string, &input_expression[*i], 5);
}

int check_is_cos(char input_expression[], int* i) {
  char cos_string[] = "cos(\0";
  // printf("------------------------------------------\n");
  // printf("Check is cos: %s", &input_expression[*i]);
  // printf("cos_string: %s\n", cos_string);
  // printf("Strncmp: %d\n", strncmp(cos_string, &input_expression[*i], 4));
  return strncmp(cos_string, &input_expression[*i], 4);
}

int check_is_acos(char input_expression[], int* i) {
  char acos_string[] = "acos(\0";
  // printf("------------------------------------------\n");
  // printf("Check is acos: %s", &input_expression[*i]);
  // printf("acos_string: %s\n", acos_string);
  // printf("Strncmp: %d\n", strncmp(acos_string, &input_expression[*i], 5));
  return strncmp(acos_string, &input_expression[*i], 5);
}

int check_is_sqrt(char input_expression[], int* i) {
  char sqrt_string[] = "sqrt(\0";
  // printf("------------------------------------------\n");
  // printf("Check is sqrt: %s", &input_expression[*i]);
  // printf("sqrt_string: %s\n", sqrt_string);
  // printf("Strncmp: %d\n", strncmp(sqrt_string, &input_expression[*i], 5));
  return strncmp(sqrt_string, &input_expression[*i], 5);
}

int check_is_ln(char input_expression[], int* i) {
  char ln_string[] = "ln(\0";
  // printf("------------------------------------------\n");
  // printf("Check is ln: %s", &input_expression[*i]);
  // printf("ln_string: %s\n", ln_string);
  // printf("Strncmp: %d\n", strncmp(ln_string, &input_expression[*i], 3));
  return strncmp(ln_string, &input_expression[*i], 3);
}

int check_is_log(char input_expression[], int* i) {
  char log_string[] = "log(\0";
  // printf("------------------------------------------\n");
  // printf("Check is log: %s", &input_expression[*i]);
  // printf("log_string: %s\n", log_string);
  // printf("Strncmp: %d\n", strncmp(log_string, &input_expression[*i], 4));
  return strncmp(log_string, &input_expression[*i], 4);
}

int check_is_mod(char input_expression[], int* i) {
  char mod_string[] = "mod\0";
  // printf("------------------------------------------\n");
  // printf("Check is mod: %s", &input_expression[*i]);
  // printf("mod_string: %s\n", mod_string);
  // printf("Strncmp: %d\n", strncmp(mod_string, &input_expression[*i], 3));
  return strncmp(mod_string, &input_expression[*i], 3);
}

int check_is_u_minus(char input_expression[], int* i) {
  char u_minus_string[] = "u_minus\0";
  return strncmp(u_minus_string, &input_expression[*i], 7);
}

int check_is_u_plus(char input_expression[], int* i) {
  char u_plus_string[] = "u_plus\0";
  return strncmp(u_plus_string, &input_expression[*i], 6);
}