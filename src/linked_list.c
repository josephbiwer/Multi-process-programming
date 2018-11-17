#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"



/************************************************************************************************
 *                                  Private fn declarations                                     *
 ************************************************************************************************/
static struct Node* create_node(time_t, struct Node*, struct Node*);
static struct Node* create_node_v2(void);

/************************************************************************************************
 *                                    Private variables                                         *
 ************************************************************************************************/
static int length;
static struct Node *root;
static struct Node *end;

void linked_init(void) {
    root = NULL;
    end = NULL;
    length = 0;
}

/************************************************************************************************
 *                                    Public Functions                                          *
 ************************************************************************************************/

void linked_add(time_t _time) {

    if(root == NULL) {

        printf("adding root node\n");

        // Creating new root node
        root = malloc(sizeof(struct Node));
        root->time = _time;
        root->previous = NULL;
        root->next = NULL;

        length++;
        end = root;

    } else {

        struct Node *temp = root;
        while(temp != NULL) {
            // Traverse linked list until we find a valid location for the time

            if(temp->next != NULL) {
                if(_time < temp->time) {            // Belongs before current node, in other words: at beginning of the list
                    
                    // Creating new node
                    struct Node *new_node = malloc(sizeof(struct Node));
                    new_node->time = _time;
                    new_node->previous = NULL;
                    new_node->next = temp;

                    // Old root points to new root
                    temp->previous = new_node;

                    length++;
                    return;

                } else if(temp->time <= _time && temp->next->time > _time) {     // Middle of the linked list
                    
                    // Create new node
                    struct Node *new_node = malloc(sizeof(struct Node));         // create_node(_time, temp->next, temp);
                    new_node->time = _time;
                    new_node->previous = temp;
                    new_node->next = temp->next;

                    // Have old "next" node's previous pointer point to the new node
                    temp->next->previous = new_node;
                    // Next pointer points to new node
                    temp->next = new_node;

                    length++;
                    return;

                }

                // If the program gets to this point, it will not do anything and will not return

            } else {        // end of the list: _time > temp->time

                // Creating new node
                struct Node *new_node = malloc(sizeof(struct Node));        // create_node(_time, NULL, temp);
                new_node->time = _time;
                new_node->next = NULL;
                new_node->previous = temp;

                // Previous end pointer now points to new end
                temp->next = new_node;
                end = new_node;
                length++;
                return;
            }
            temp = temp->next;
        }
    }
}

void linked_destroy (void) {
    struct Node *temp, *prev;
    while(temp != NULL) {
        prev = temp;
        temp = temp->previous;
        free(prev);
        length--;
    }
}

time_t linked_getEnd(void) {
    return end->time;
}

time_t linked_getRoot(void) {
    return root->time;
}

void linked_print(void) {
    struct Node *temp = root;
    while(temp != NULL) {
        printf("time = %ld\n", temp->time);
        temp = temp->next;
    }
}

void linked_removeFirst(void) {
    if(root != NULL) {
        struct Node *temp = root;
        root = root->next;
        if(root != NULL)
            root->previous = NULL;
        free(temp);
        length--;
    }
}

bool linked_empty(void) {
    return root == NULL;
}

int linked_size(void) {
    return length;
}

/************************************************************************************************
 *                                    Private Functions                                          *
 ************************************************************************************************/


static struct Node* create_node(time_t _time, struct Node *_next, struct Node *_previous) {
    struct Node *temp;
    temp = (struct Node*) malloc(sizeof(struct Node));
    temp->previous = _previous;
    temp->next = _next;
    temp->time = _time;
    return temp;
}

static struct Node* create_node_v2(void) {
    struct Node *temp = (struct Node*) malloc(sizeof(struct Node));
    return temp;
}