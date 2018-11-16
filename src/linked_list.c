#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"



/************************************************************************************************
 *                                  Private fn declarations                                     *
 ************************************************************************************************/
struct Node* create_node(time_t, struct Node*, struct Node*);


static struct Node *root;
static struct Node *end;

void linked_init(void) {
    root = NULL;
    end = NULL;
}

void linked_add(time_t _time) {
    if(root == NULL) {
        root = create_node(_time, NULL, NULL);
        printf("after return in root");
    } else {
        printf("not root node\n");
        struct Node *temp = root;
        while(temp != NULL) {
            printf("temp->time: %ld\n", temp->time);
            // Traverse linked list until we find a valid location for the time
            if(temp->next != NULL) {
                if(_time < temp->time) {            // Belongs before current node, in other words: at beginning of the list
                    // Creating new node
                    struct Node *new_node = create_node(_time, temp, NULL);
                    // Old root points to new root
                    temp->previous = new_node;
                } else if(temp->time <= _time && temp->next->time > _time) {     // Middle of the linked list
                    // Create new node
                    struct Node *new_node = create_node(_time, temp->next, temp);
                    // Have old "next" node's previous pointer point to the new node
                    temp->next->previous = new_node;
                    // Next pointer points to new node
                    temp->next = new_node;
                } else {        // end of the list: _time > temp->time
                    // Creating new node
                    struct Node *new_node = create_node(_time, NULL, temp);
                    // Previous end pointer now points to new end
                    temp->next = new_node;
                }
            }
        }
    }
}



void linked_destroy (void) {
    struct Node *temp, *prev;
    while(temp != NULL) {
        prev = temp;
        temp = temp->previous;
        free(prev);
    }
}

time_t linked_getEnd(void) {
    return end->time;
}



struct Node* create_node(time_t _time, struct Node *_next, struct Node *_previous) {
    struct Node *temp = malloc(sizeof(struct Node));
    temp->previous = _previous;
    temp->next = _next;
    temp->time = _time;
    printf("right before return statement in create_node\n");
    return temp;
}