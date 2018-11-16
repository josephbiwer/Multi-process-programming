#ifndef LINKED_LIST
#define LINKED_LIST

#include <time.h>

struct Node {
    time_t time;
    struct Node *next;
    struct Node *previous;
};

void linked_init(void);
void linked_add(time_t);
time_t linked_getEnd(void);

#endif