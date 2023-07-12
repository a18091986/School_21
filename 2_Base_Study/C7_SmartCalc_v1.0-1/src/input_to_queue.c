#include "input_to_queue.h"


int from_input_to_queue(char input_expression[256], queue * result_queue, double x_val) {
    int is_previous_operand = 0;
    int res = 1;
    printf("X: %lf\n", x_val);
    // queue_head(&result_queue);

    int length_of_ie = (int) strlen(input_expression);
    printf("Длина входной строки: %d\n-----------------------\n", length_of_ie);

    int i = 0;

    while (i != length_of_ie - 1) {
    // while (input_expression[i] != '\0') {
        // printf("Symbol: %c\n", input_expression[i]);
        // printf("Current symbol: %c\n", input_expression[i]);
        if (input_expression[i] == ' ') {
            pass_spaces(input_expression, &i);
        }
        if (input_expression[i] == '.') {
            printf("Point not in number");
            res = 0;
            i++;
        } 
        else if (input_expression[i] == '+' || input_expression[i] == '-') {
            // printf("i: %d\n", i);
            int plus_or_minus_flag = check_plus_or_minus(input_expression, &i);
            char plus_or_minus[2]={'\0'}; 
            strcpy(plus_or_minus, plus_or_minus_flag == 0 ? "+" : "-");
            int is_unar = is_previous_operand ? 0 : 1;
            insert_queue(result_queue, plus_or_minus, is_unar);
            is_previous_operand = 0;
        } 
        else if (strchr("0123456789", input_expression[i])) {
            char number[17]={'\0'};
            if (!get_digits(input_expression, &i, number)) {
                printf("Incorrect number\n");
                res = 0;     
            } else {
            res = insert_queue(result_queue, number, 0);
            is_previous_operand = 1;
            }
        } 
        else if (input_expression[i] == '(') {
            res = insert_queue(result_queue, "(", 1);
            i++;
        } 
        else if (input_expression[i] == ')') {
            res = insert_queue(result_queue, ")", 1);
            i++;
        } 
        else if (check_is_sin(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "sin", 1);
            is_previous_operand = 0;
            i += 3;
        }
        else if (check_is_asin(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "asin", 1);
            is_previous_operand = 0;
            i += 4;
        }
        else if (check_is_cos(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "cos", 1);
            is_previous_operand = 0;
            i += 3;
        } 
        else if (check_is_acos(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "acos", 1);
            is_previous_operand = 0;
            i += 4;
        } 
        else if (check_is_tan(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "tan", 1);
            is_previous_operand = 0;
            i += 3;
        } 
        else if (check_is_atan(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "atan", 1);
            is_previous_operand = 0;
            i += 4;
        } 
        else if (check_is_sqrt(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "sqrt", 1);
            is_previous_operand = 0;
            i += 4;
        } 
        else if (check_is_ln(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "ln", 1);
            is_previous_operand = 0;
            i += 2;
        } 
        else if (check_is_log(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "log", 1);
            is_previous_operand = 0;
            i += 3;
        } 
        else if (check_is_mod(input_expression, &i) == 0) {
            res = insert_queue(result_queue, "mod", 0);
            is_previous_operand = 0;
            i += 3;
        }
        else {
            printf("No match in input_to_queue function\n");
            res = 0;
        }
        if (res == 0)
            break;
    }
    return res;
};

void read_lex() {
    printf("from read_lex");
}

void pass_spaces(char input_expression[], int * i) {
    while (input_expression[*i] == ' ') (*i)++;
}


int check_plus_or_minus(char input_expression[], int * i) {  
    int minus_count = 0;
    int plus_count = 0;

    while ((input_expression[*i] == '+') || (input_expression[*i] == '-')) {
        if (input_expression[*i] == '-')
            minus_count++;
        else
            plus_count++;
        (*i)++;
    }
    int res = (- minus_count + plus_count) >= 0 ? 0 : 1;
    // printf("--------------------------------------------\n");
    // printf("from check_plus_or_minus: \n");
    // printf("Minus count: %d, Plus count: %d\n", minus_count, plus_count);
    // printf("Result: %d. If 0 => +, else - \n", res);
    // printf("Next symbol: %c\n", input_expression[*i]);
    return res;
}

int get_digits(char input_expression[], int * i, char digits_string[]) {
    int res = 1;
    int count = 0;
    int point_count = 0;
    int j = *i;
    while (strchr("0123456789.", input_expression[*i])) {
        if (input_expression[*i] == '.')
            point_count++;
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

// int check_is_unar(char input_expression[], int * i, int is_previous_operand) {
//     // проверка унарный или бинарный + или -
//     // return 0 - бинарный, 1 - унарный
//     return is_previous_operand >= 0 ? 0 : 1;
// }

int check_is_sin(char input_expression[], int * i) {
    char sin_string [] = "sin(\0";
    // printf("------------------------------------------\n");
    // printf("Check is sin: %s", &input_expression[*i]);
    // printf("sin_string: %s\n", sin_string);
    // printf("Strncmp: %d\n", strncmp(sin_string, &input_expression[*i], 3));
    return strncmp(sin_string, &input_expression[*i], 4);
}

int check_is_asin(char input_expression[], int * i) {
    char asin_string [] = "asin(\0";
    // printf("------------------------------------------\n");
    // printf("Check is asin: %s", &input_expression[*i]);
    // printf("asin_string: %s\n", asin_string);
    // printf("Strncmp: %d\n", strncmp(asin_string, &input_expression[*i], 5));
    return strncmp(asin_string, &input_expression[*i], 5);
}

int check_is_tan(char input_expression[], int * i) {
    char tan_string [] = "tan(\0";
    // printf("------------------------------------------\n");
    // printf("Check is tan: %s", &input_expression[*i]);
    // printf("tan_string: %s\n", tan_string);
    // printf("Strncmp: %d\n", strncmp(tan_string, &input_expression[*i], 4));
    return strncmp(tan_string, &input_expression[*i], 4);
}

int check_is_atan(char input_expression[], int * i) {
    char atan_string [] = "atan(\0";
    // printf("------------------------------------------\n");
    // printf("Check is atan: %s", &input_expression[*i]);
    // printf("atan_string: %s\n", atan_string);
    // printf("Strncmp: %d\n", strncmp(atan_string, &input_expression[*i], 5));
    return strncmp(atan_string, &input_expression[*i], 5);
}

int check_is_cos(char input_expression[], int * i) {
    char cos_string [] = "cos(\0";
    // printf("------------------------------------------\n");
    // printf("Check is cos: %s", &input_expression[*i]);
    // printf("cos_string: %s\n", cos_string);
    // printf("Strncmp: %d\n", strncmp(cos_string, &input_expression[*i], 4));
    return strncmp(cos_string, &input_expression[*i], 4);
}

int check_is_acos(char input_expression[], int * i) {
    char acos_string [] = "acos(\0";
    // printf("------------------------------------------\n");
    // printf("Check is acos: %s", &input_expression[*i]);
    // printf("acos_string: %s\n", acos_string);
    // printf("Strncmp: %d\n", strncmp(acos_string, &input_expression[*i], 5));
    return strncmp(acos_string, &input_expression[*i], 5);
}

int check_is_sqrt(char input_expression[], int * i) {
    char sqrt_string [] = "sqrt(\0";
    // printf("------------------------------------------\n");
    // printf("Check is sqrt: %s", &input_expression[*i]);
    // printf("sqrt_string: %s\n", sqrt_string);
    // printf("Strncmp: %d\n", strncmp(sqrt_string, &input_expression[*i], 5));
    return strncmp(sqrt_string, &input_expression[*i], 5);
}

int check_is_ln(char input_expression[], int * i) {
    char ln_string [] = "ln(\0";
    // printf("------------------------------------------\n");
    // printf("Check is ln: %s", &input_expression[*i]);
    // printf("ln_string: %s\n", ln_string);
    // printf("Strncmp: %d\n", strncmp(ln_string, &input_expression[*i], 3));
    return strncmp(ln_string, &input_expression[*i], 3);
}

int check_is_log(char input_expression[], int * i) {
    char log_string [] = "log(\0";
    // printf("------------------------------------------\n");
    // printf("Check is log: %s", &input_expression[*i]);
    // printf("log_string: %s\n", log_string);
    // printf("Strncmp: %d\n", strncmp(log_string, &input_expression[*i], 4));
    return strncmp(log_string, &input_expression[*i], 4);
}

int check_is_mod(char input_expression[], int * i) {
    char mod_string [] = "mod\0";
    // printf("------------------------------------------\n");
    // printf("Check is mod: %s", &input_expression[*i]);
    // printf("mod_string: %s\n", mod_string);
    // printf("Strncmp: %d\n", strncmp(mod_string, &input_expression[*i], 3));
    return strncmp(mod_string, &input_expression[*i], 3);
}