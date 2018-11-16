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

#include "app.h"
#include "../inc.h"
#include "linked_list.h"


static int total;
static int walker;
static time_t *times;


void killHandler(int _sig) {
	// printf("inside killHandler\n");
	kill(getpid(), SIGUSR1);
}

void alarmHandler(int _sig) {
	printf("time = %ld: Alarm occurred\n", time(NULL));
	signal(SIGALRM, SIG_IGN);
	walker++;
	signal(SIGALRM, alarmHandler);
	alarm(times[walker] - times[walker-1]);
}

void usr1Handler(int _sig) {
	printf("time = %ld, SIGUSR1 caught\n", time(NULL));
	printf("time = %ld: alarm %d added, alarm time = %ld\n", time(NULL), walker, times[walker]);
}


int main(int argc, char **argv) {

	// Random number seed
	srand(time(NULL));

	if(argc <= 1) {
		printf("Please enter in amount of times to generate\n");
		return 0;
	}

	linked_init();		// Initializing linked list
	linked_add(time(NULL));		// Adding current time to the beginning of the list
	total = atoi(argv[1]);

	// times = malloc(sizeof(time_t) * total);

	// times[0] = time(NULL);
	// printf("time = %ld: initial list =", times[0]);
	int i;
	for(i = 1; i <= total; i++) {
		time_t new_time = linked_getEnd() + rand() % MAX_TIME + 1;
		linked_add(new_time);
	}

	return 0;

	walker = 1;
	alarm(times[walker] - times[walker-1]);



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

	// Wait until <1st cmd line argument> kill commands have been entered
	while(walker <= total) {
		pause();
	}

	return 0;
}