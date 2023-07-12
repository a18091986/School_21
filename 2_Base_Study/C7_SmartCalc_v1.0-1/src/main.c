#include "stack.h" 
#include "queue.h"
#include "input_to_queue.h"

typedef struct Test {
    float x,y,z;
} Test;

int main() {
    
// --------------------------------INPUT_TO_QUEUE--------------------------------

char input_string[256] = {0};
queue q;
double x = 1.1;

init_queue(&q);

fgets(input_string, 255, stdin);
from_input_to_queue(input_string, q, x);


queue_head(&q);
char t[17];
while (get_from_queue(&q, t))
    printf("val: %s\n", t);



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
    //     printf("Name: %s, x=%f, y=%f, z=%f\n", t->name, test->x, test->y, test->z);
    //     t = t->next;
    // };

    // char name_to_find[20];
    // scanf("%s", name_to_find);
    // StackElement * find = findStackElement(top, name_to_find);
    // if (find) printf("Found\n");
    // else printf("Not found\n");

    // freeStack(top);

    return 0;
}