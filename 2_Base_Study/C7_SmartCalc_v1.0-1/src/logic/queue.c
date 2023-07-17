#include "logic/queue.h"

void init_queue(queue *q) {
  q->head = NULL;
  q->tail = NULL;
}

void queue_head(queue *q) {
  if (q->head)
    printf("Not NULL\n");
  else
    printf("NULL\n");
}

int insert_queue(queue *q, char value[], char type[]) {
  int result = 1;

  // создание нового элемента очереди
  node *newnode = malloc(sizeof(node));
  if (!newnode) result = 0;

  strcpy(newnode->value, value);
  strcpy(newnode->type, type);
  newnode->next = NULL;

  // проверка, если очередь не пуста, то новый элемент становится её концом,
  // а следующий начинается ссылаться на новый
  if (q->tail != NULL) {
    q->tail->next = newnode;
  }
  q->tail = newnode;

  // если очередь пуста, то новый элемент становится и началом и концом
  if (q->head == NULL) q->head = newnode;

  return result;
}

int get_from_queue(queue *q, char *value, char *type) {
  int res = 1;
  if (q->head == NULL)
    res = 0;
  else {
    node *tmp = q->head;
    strcpy(value, tmp->value);
    strcpy(type, tmp->type);

    q->head = q->head->next;

    if (q->head == NULL) q->tail = NULL;

    free(tmp);
  }
  return res;
}

// void free_queue (queue * q) {

//     while (q -> head) {
//         get
//     }
// }
