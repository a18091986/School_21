#include "polish.h"

int get_prior(char * operator) {
    int prior;
    if (!strcmp(operator, "+") || !strcmp(operator, "-")) {
        prior = 1;
    } else if (!strcmp(operator, "*") || !strcmp(operator, "/") || !strcmp(operator, "mod")) {
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

int form_polish_string(queue * q, StackElement * s, char postfix[256]) {
    printf("----------------------------------------------\npolish\n");
    int j = 0; // outer_string_pointer
    // printf("FROM FORM POLISH\n");
    node tmp;
    
    // char t[17];
    // char operator_or_operand[10];
    // int is_unar;
    while (get_from_queue(q, tmp.value, tmp.type)) {
        
        if (strcmp(tmp.type, "operand") == 0) {
            // printf("Operand: %s\n", tmp.value);
            strncpy(&postfix[j], tmp.value, strlen(tmp.value));
            j += strlen(tmp.value);
            strncpy(&postfix[j++], " ", 1);
        }
        else if (strcmp(tmp.value, ")") == 0) {
            ;
        }
        else if (strcmp(tmp.value, "(") == 0 || strcmp(tmp.value, "sqrt") == 0 || 
                 strcmp(tmp.value, "u_plus") == 0 || strcmp(tmp.value, "u_minus") == 0 ||
                 strcmp(tmp.value, "cos") == 0 || strcmp(tmp.value, "acos") == 0 ||
                 strcmp(tmp.value, "sin") == 0 || strcmp(tmp.value, "asin") == 0 ||
                 strcmp(tmp.value, "tan") == 0 || strcmp(tmp.value, "atan") == 0 ||
                 strcmp(tmp.value, "log") == 0 || strcmp(tmp.value, "ln") == 0) {
            // printf("Operator: %s\n", tmp.value);
            s = pushStackElement(s);
            setStackElementName(s, tmp.value);
            setStackElementData(s, &tmp, sizeof(tmp));
        }
        else if (strcmp(tmp.value, "+") == 0 || strcmp(tmp.value, "-") == 0 ||
                 strcmp(tmp.value, "/") == 0 || strcmp(tmp.value, "*") == 0 ||
                 strcmp(tmp.value, "mod") == 0 || strcmp(tmp.value, "^") == 0) {
            // printf("Operator: %s\n", tmp.value);
            while (s && get_prior(tmp.value) <= 
                          get_prior(s->data->value)) {
                char current_operator_from_stack[10];
                strcpy(current_operator_from_stack, s->name);
                strcpy(&postfix[j], current_operator_from_stack);
                // strcpy(&postfix[j+1], " ");
                // printf("Higher priority: %s\n", current_operator_from_stack);
                j += strlen(current_operator_from_stack); 
                strncpy(&postfix[j++], " ", 1);
                // postfix[++j] = ' ';    
                s = popStackElement(s);
            }
            s = pushStackElement(s);
            setStackElementName(s, tmp.value);
            setStackElementData(s, &tmp, sizeof(tmp));
        } 
    }
    while (s) {
        char current_operator_from_stack[10];
        strcpy(current_operator_from_stack, s->name);
        strcpy(&postfix[j], current_operator_from_stack);
        // strcpy(&postfix[j+1], " ");
        j += strlen(current_operator_from_stack);
        strncpy(&postfix[j++], " ", 1);     
        // postfix[++j] = ' ';
        s = popStackElement(s);
    }
    // show_stack(s);


    // double sum = 0;
    // printf("------------\n");
    // while(s) {
    //     char[] lex_type = 
    //     // node * temp = (node*)s->data;
    //     if (strcmp((((node*)s->data)->type), "operand") == 0) {
    //         strncpy(&postfix[j], ((node*)s->data)->value, strlen(((node*)s->data)->value));
    //         j += strlen(((node*)s->data)->value);
    //     }
    //     else if (strcmp((((node*)s->data)->type), "operator") == 0)
    //         current_operator_prior = get_prior()
    //         while ((node*)(popStackElement(s)->data))
    //         if 

    //     }
    //         // printf("%s\n", (((node*)s->data)->value));   
    //     s = s->next;
    // };
    printf("POSTFIX_STRING: %s\n", postfix);
    printf("polish\n----------------------------------------------\n");
    return 0;
}