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


void generate_times (time_t *_times, int _size) {
    if(_size > 0) {

        time_t current_time = time(NULL);

        printf("before assigning time 0");

        *_times = 2;
        // alarm(_times[0]);

        printf("time 0: %ld\n", _times[0]);

        int i;
        for(i = 1; i < _size; i++) {
            int random_time = rand() % MAX_TIME + 1;
            *(_times + i) = *(_times + i - 1) + (rand() % MAX_TIME) + 1;
            printf("time %d: %ld\n\n", i, *(_times + i));
        }
    }
}