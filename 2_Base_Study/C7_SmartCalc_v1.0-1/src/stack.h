#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STACK_H
#define STACK_H

typedef struct StackElement {
    char * name;
    void * data;
    struct StackElement * next;
} StackElement;

StackElement * pushStackElement(StackElement * top);
StackElement * popStackElement(StackElement * top);
StackElement * findStackElement(StackElement * top, char * name);

void freeStack(StackElement * top);
void setStackElementName(StackElement * top, char * name);
void setStackElementData(StackElement * top, void * data, unsigned int datasize);


#endif

// https://www.youtube.com/watch?v=vyp97yTCsQU