#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef QUEUE_H
#define QUEUE_H

typedef struct node {
    char value[17];
    int is_unar;
    struct node * next;   
} node;

typedef struct {
    node * head;
    node * tail;
} queue;

void init_queue (queue *q);
void queue_head (queue *q);

int insert_queue (queue * q, char * value, int is_unar);
// 1 - Успешное добавление в очередь, 0 - ошибка при выделении памяти

int get_from_queue (queue * q, char *result, int * is_unar);
// 1 - успешно возвращено значение элемента очереди, 
// 0 - очередь пуста


#endif