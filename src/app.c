/**
 * Author: Joe Biwer
 * Date: November 11, 2018
 * Description: Implementation of functions used for signal and alarm application
 */


#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "app.h"
#include "../inc.h"
#include "linked_list.h"


void generate_times (int total) {
    linked_init();				// Initializing linked list
	linked_add(time(NULL));		// Adding current time to the beginning of the list
	
	printf("current time: %ld,", linked_getRoot());
    fflush(stdout);
	int i;
	for(i = 1; i <= total; i++) {
		time_t new_time = linked_getEnd() + rand() % MAX_TIME + 1;
        printf(" (%d, %ld)", i, new_time);
        fflush(stdout);
		linked_add(new_time);
	}
    printf("\n");
}