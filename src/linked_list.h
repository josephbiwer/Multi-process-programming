#ifndef LINKED_LIST
#define LINKED_LIST

#include <time.h>
#include <stdbool.h>

struct Node {
    time_t time;
    struct Node *next;
    struct Node *previous;
};

void linked_init(void);
void linked_print(void);

void linked_add(time_t);
void linked_removeFirst(void);

bool linked_empty(void);
int linked_size(void);

time_t linked_getEnd(void);
time_t linked_getRoot(void);

#endif