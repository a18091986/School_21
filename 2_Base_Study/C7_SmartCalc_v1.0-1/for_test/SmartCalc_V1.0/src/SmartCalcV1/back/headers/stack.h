/**
 * @file stack.h
 * @brief A stack implementation for storing lexema.
 */
#ifndef SRC_SMARTCALCV1_BACK_HEADERS_STACK_H_
#define SRC_SMARTCALCV1_BACK_HEADERS_STACK_H_

#include "includes.h" /**< Necessary header files for backend module. */

/**
 * @brief The maximum limit for the input expression.
 */
#define MAX_LIMIT 1024

/**
 * @brief The set of valid digits in the input expression.
 */
#define DIGITS "0123456789x.Pe"

/**
 * @brief The set of valid signs in the input expression.
 */
#define SIGNS "*-+/^"

/**
 * @brief The set of starting chars of trigonometric functions in the input
 * expression.
 */
#define TRIGONMETRY "scltma"

/**
 * @brief The set of valid chars for processing trigonometric functions.
 */
#define OPERATIONS "SsCcTtRlL"

/**
 * @brief The set of valid binary operators in the input expression.
 */
#define VALIDATION "*-+/^%~"

/**
 * @struct InputNode
 * @brief A node in the stack that stores a string.
 */
typedef struct input_node {
  char *lexema;            /**< The lexema stored in the node. */
  struct input_node *next; /**< Pointer to the next node in the stack. */
} InputNode;

/**
 * @struct Stack
 * @brief A stack data structure for storing strings.
 */
typedef struct {
  InputNode *top; /**< Pointer to the top node in the stack. */
  int x_status;   /**< An integer status code. */
  char *x_value;  /**< A string value. */
} Stack;

/**
 * @brief Initializes a new stack.
 *
 * @return A pointer to the new stack.
 */
Stack *initStack();

/**
 * @brief Checks if the stack is empty.
 *
 * @param input A pointer to the stack.
 * @return 1 if the stack is empty, 0 otherwise.
 */
int isEmpty(Stack *s);

/**
 * @brief Pushes a new string onto the stack.
 *
 * @param input A pointer to the stack.
 * @param value The string to push onto the stack.
 */
void push(Stack *input, char *value);

/**
 * @brief Pops the top string off the stack.
 *
 * @param input A pointer to the stack.
 * @return The string that was popped off the stack.
 */
char *pop(Stack *input);

/**
 * @brief Returns the top string on the stack without removing it.
 *
 * @param input A pointer to the stack.
 * @return The top string on the stack.
 */
char *peek(Stack *input);

/**
 * @brief Frees the memory used by the stack.
 *
 * @param input A pointer to the stack.
 */
void freeStack(Stack *input);

/**
 * @brief Reverses the order of the strings in the stack.
 *
 * @param stack A pointer to the stack.
 */
void reverseStack(Stack *stack);

/**
 * @brief Creates a copy of the stack.
 *
 * @param stack A pointer to the stack to copy.
 * @return A pointer to the new stack.
 */
Stack *copyStack(Stack *stack);

Stack *rpnConverter(Stack *input);
void operationHandler(Stack *rpn_stack, Stack *temp_stack, char *pop_value);
int priorityValidation(Stack *temp_stack, int peek_priority, int pop_priority);
int checkPriority(char oper);

#endif  // SRC_SMARTCALCV1_BACK_HEADERS_STACK_H_
