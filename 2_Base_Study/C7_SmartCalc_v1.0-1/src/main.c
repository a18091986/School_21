#include "main.h"

int main() {
  // --------------------------------INPUT_TO_QUEUE--------------------------------
  int err = 0;
  double result = 0.0;
  char input_string[512] = {'\0'};
  char polish_string[512] = {'\0'};
  double x = 1.1;

  queue q_in;
  queue q_polish;

  StackElement* s_in = NULL;
  StackElement* s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  fgets(input_string, 511, stdin);

  result = back_process(input_string, polish_string, x, &q_in, &q_polish, s_in,
                        s_pol, &err);
  if (!err) printf("Result: %lf\n", result);
  return 0;
}

// node test;
// while (get_from_queue (&q_polish, test.value, test.type))
//     printf("value: %s, type: %s\n", test.value, test.type);

// ------------------------------------QUEUE--------------------------------------

// queue q1;
// init_queue(&q1);

// insert_queue(&q1, 15);
// insert_queue(&q1, 31);
// insert_queue(&q1, 45);

// int t;

// while (get_from_queue(&q1, &t))
//     printf("val: %d\n", t);

// ------------------------------------STACK---------------------------------------
// Test test;
// StackElement * top = NULL;
// char buf[100];
// char name[20];

// printf("Name, x y z or q to exit\n");

// while(fgets(buf, 99, stdin) != NULL) {
//     sscanf(buf, "%s %f %f %f", name, &test.x, &test.y, &test.z);
//     if (strcmp(name, "q") == 0) break;
//     top = pushStackElement(top);
//     setStackElementName(top, name);
//     setStackElementData(top, &test, sizeof(Test));
// };

// printf("------------\n");
// StackElement * t = top;
// while(t) {
//     Test * test = (Test*)t->data;
//     printf("Name: %s, x=%f, y=%f, z=%f\n", t->name, test->x, test->y,
//     test->z); t = t->next;
// };

// char name_to_find[20];
// scanf("%s", name_to_find);
// StackElement * find = findStackElement(top, name_to_find);
// if (find) printf("Found\n");
// else printf("Not found\n");

// freeStack(top);
