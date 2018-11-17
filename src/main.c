/**
 * Author: Joe Biwer
 * Date: November 7, 2018
 * Description: Project 6 - Signals
 */


#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>

#include "app.h"
#include "../inc.h"
#include "linked_list.h"


static int total;
static int walker;
static time_t *times;


void killHandler(int _sig) {
	kill(getpid(), SIGUSR1);
}

void alarmHandler(int _sig) {
	signal(SIGALRM, SIG_IGN);

	printf("time = %ld: Alarm occurred\n", time(NULL));

	if(linked_size() > 1) {
		time_t prev = linked_getRoot();
		linked_removeFirst();
		while(linked_getRoot() == prev) {
			linked_removeFirst();
		}
		signal(SIGALRM, alarmHandler);
		alarm(linked_getRoot() - prev);
	} else {
		linked_removeFirst();
	}
}

void usr1Handler(int _sig) {
	printf("time = %ld: SIGUSR1 caught\n", time(NULL));
	time_t new_time = linked_getRoot() + rand() % MAX_TIME + 1;
	printf("time = %ld: alarm added, alarm time = %ld\n", time(NULL), new_time);
	linked_add(new_time);
	// printf("\n------------\n");
	// linked_print();
	// printf("------------\n\n");
}


int main(int argc, char **argv) {

	// Random number seed
	srand(time(NULL));

	if(argc <= 1) {
		printf("Please enter in amount of times to generate\n");
		return 0;
	}

	total = atoi(argv[1]);

	generate_times(total);

	time_t first = linked_getRoot();
	linked_removeFirst();



	// Declaring signal handler
	struct sigaction sa;
	sa.sa_handler = killHandler;			// Only requires one parameter, opposed to setting 'sa_sigaction'
	if( sigaction(SIGTERM, &sa, NULL ) < 0) {
		printf("Error encountered with sigaction\n");
		return 1;
	}

	// SIGUSR
	signal(SIGUSR1, usr1Handler);

	// Declaring signal handler for alarms
	signal(SIGALRM, alarmHandler);

	alarm(linked_getRoot() - first);

	// Wait until <1st cmd line argument> kill commands have been entered
	while(!linked_empty()) {
		pause();
	}

	return 0;
}