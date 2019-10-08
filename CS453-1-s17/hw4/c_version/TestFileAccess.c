/**
 * TestFileAccess.c
 *
 * @Since: Mar 9, 2017
 * @Author: yi xie
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include "FileAccess.h"

void *threadMain(void *);
pthread_t *tids;

FileAccessPtr flptr;

long int numThreads;
long int maxSum;
long int iteration;

pthread_mutex_t mutex;

void signalHandler(int);

/**
 * main function
 */
int main(int argc, char **argv)
{
    int i;

    if (argc < 3) {
	    fprintf(stderr, "Usage: %s <numThreads> < max sum> <iterations>\n", argv[0]);
	    exit(1);
    }

    numThreads  = atoi(argv[1]);
    maxSum = atoi(argv[2]);
    iteration = atoi(argv[3]);

    if (numThreads > 32) {
	    fprintf(stderr, "Usage: %s Too many threads specified. Defaulting to 32.\n", argv[0]);
	    numThreads = 32;
    }

    flptr = fileaccess_init(maxSum);
    signal(SIGALRM, signalHandler);
    alarm(30);


    pthread_mutex_init(&mutex, NULL);
    tids = (pthread_t *) malloc(sizeof(pthread_t)*numThreads);
    for (i=1; i<= numThreads; i++) {
    	pthread_create(&tids[i], NULL, threadMain, (void *) NULL);
	}

    for (i=1; i<= numThreads; i++)
    	pthread_join(tids[i], NULL);

    pthread_mutex_destroy(&mutex);
    exit(0);
}

/**
 * get current thread id
 * @return i thread id number
 */
int get_my_index()
{
    int i;
    pthread_mutex_lock(&mutex);
    for (i=1; i<= numThreads; i++)
    {
        if (tids[i] == pthread_self())
        {
            pthread_mutex_unlock(&mutex);
            return i;
        }
    }
    pthread_mutex_unlock(&mutex);
    return -1; /* we have a problem if we reach this statement */
}

/**
 * file access simulation thread
 * @param arg
 */
void *threadMain(void *arg)
{
    int i;
    int fileAccessTime;
    int id = get_my_index();

    for (i=1; i<= iteration; i++) {
	printf("Thread %d starting up.\n", id);
	(*flptr->startAccess)(flptr, id);
	fileAccessTime= random() % 4 + 1; // 1 to 4 seconds
	sleep(fileAccessTime);
	(*flptr->endAccess)(flptr, id);
	fileAccessTime= random() % 4 + 1; // 1 to 4 seconds
	sleep(fileAccessTime);
    }

    pthread_exit(NULL);
}


void signalHandler(int signo)
{
    printf("Aieeeeeee...received an alarm. Timeout!\n");	
    exit(1); //if waiting time is longer than 30 second exit the program
}

