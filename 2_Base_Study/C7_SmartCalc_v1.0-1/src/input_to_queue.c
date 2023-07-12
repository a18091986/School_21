#include "input_to_queue.h"


int from_input_to_queue(char input_expression[256], queue result_queue, double x_val) {
    int res = 0;
    printf("X: %lf\n", x_val);
    queue_head(&result_queue);

    int length_of_ie = (int) strlen(input_expression);
    printf("Длина входной строки: %d\n", length_of_ie);

    int i = 0;

    while (input_expression[i] != '\0') {
        // printf("%c", input_expression[i++]);
        if (input_expression[i] == ' ') {
            pass_spaces(input_expression, &i);
            // printf("\n");
        }
        if (input_expression[i] == '(' || input_expression[i] == ')' || 
            input_expression[i] == '+' || input_expression[i] == '-') {
            insert_queue(&result_queue, &input_expression[i]);
        } else if (input_expression[i] == 's') {
            printf("s\n");
            if (check_is_sin(input_expression, &i) == 0) {
                int res = insert_queue(&result_queue, "sin");
                printf("insert queue result: %d\n", res);
                i+=3;
            }
        } else {
            ;
        }
        i++;
    }
    char temp [17];
    printf("FROM QUEUE: %d\n", get_from_queue(&result_queue, temp));
    printf("FROM QUEUE VAL: %s\n", temp);
    return res;
};

void read_lex() {
    printf("from read_lex");
}

void pass_spaces(char input_expression[], int * i) {
    while (input_expression[*i] == ' ') (*i)++;
}


int check_is_sin(char input_expression[], int * i) {
    char sin_string [] = "sin\0";
    printf("Check is sin: %s", &input_expression[*i]);
    printf("sin_string: %s\n", sin_string);
    printf("Strncmp: %d\n", strncmp(sin_string, &input_expression[*i], 3));
    return strncmp(sin_string, &input_expression[*i], 3);
}

