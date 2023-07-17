#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logic/queue.h"
#include "main.h"

#ifndef STACK_H
#define STACK_H

typedef struct StackElement {
  char* name;
  node* data;
  double value;
  struct StackElement* next;
} StackElement;

StackElement* pushStackElement(StackElement* top);
StackElement* popStackElement(StackElement* top);
StackElement* findStackElement(StackElement* top, char* name);

void freeStack(StackElement* top);
void setStackElementName(StackElement* top, char* name);
void setStackElementData(StackElement* top, void* data, unsigned int datasize);
void show_stack(StackElement* top);

#endif

// https://www.youtube.com/watch?v=vyp97yTCsQU