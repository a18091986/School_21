#include "logic/stack.h"

StackElement *pushStackElement(StackElement *top) {
  // добавление элемента в стек
  // top - указатель на вершину имеющегося стека
  StackElement *new_el = (StackElement *)malloc(sizeof(StackElement));
  new_el->name = NULL;
  new_el->data = NULL;
  new_el->next = top;

  return new_el;
}

StackElement *popStackElement(StackElement *top) {
  StackElement *result;
  // удаление элемента из стека (с вершины)
  // top - указатель на вершину стека
  if (!top)
    result = NULL;
  else {
    if (top->name) free(top->name);
    if (top->data) free(top->data);
    result = top->next;
    free(top);
  }
  return result;
}

void freeStack(StackElement *top) {
  // очистка стека полностью
  while (top) top = popStackElement(top);
}

void setStackElementName(StackElement *top, char *name) {
  // установка имени элемента стека
  if (top->name) free(top->name);
  top->name = (char *)malloc(strlen(name) + 1);
  strcpy(top->name, name);
}

void setStackElementData(StackElement *top, void *data, unsigned int datasize) {
  // установка данных элемента стека
  if (top->data) free(top->data);
  top->data = malloc(datasize);
  memcpy(top->data, data, datasize);
}

// StackElement *findStackElement(StackElement *top, char *name) {
//   // поиск элемента в стеке по имени
//   StackElement *result = NULL;
//   while (top) {
//     if (strcmp(top->name, name) == 0) {
//       result = top;
//       break;
//     }
//     top = top->next;
//   };
//   return result;
// }

// void show_stack(StackElement *top) {
//   printf("Current Stack:\n");
//   while (top) {
//     printf("Elemement_name: %s, value: %lf, data_value: %s\n", top->name,
//            top->value, top->data->value);
//     top = top->next;
//   }
// }