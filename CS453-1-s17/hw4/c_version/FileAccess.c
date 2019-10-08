/**
 * FileAccess.c
 *
 * @Since: Mar 9, 2017
 * @Author: yxie
 */

#include <stdlib.h>
#include <stdio.h>
#include "FileAccess.h"
#include <pthread.h>

static void startAccess(FileAccessPtr, int);
static void endAccess(FileAccessPtr, int);

/**
 * init fileaccess pointer
 * @param max max of sum of thread id
 * @return fileaccess pointer
 */
FileAccessPtr fileaccess_init(int max)
{
	FileAccessPtr flptr = (FileAccessPtr) malloc(sizeof(FileAccess));
	flptr->sum = 0;
	flptr->max = max;
	flptr->startAccess = startAccess;
	flptr->endAccess = endAccess;
	pthread_mutex_init(&(flptr->mutex), NULL);
	pthread_cond_init(&(flptr->waitForAccess), NULL);
	return flptr;
}

/**
 * start file access
 * @param flptr fileaccess pointer
 * @param id thread id
 */
void startAccess(FileAccessPtr flptr, int id)
{
	pthread_mutex_lock(&(flptr->mutex));

	flptr->sum = flptr->sum + id;
	printf("Thread %d starting file access.\n", id);
	while (flptr->sum > flptr->max) {
		pthread_cond_wait(&(flptr->waitForAccess), &(flptr->mutex));
	}
	pthread_cond_signal(&(flptr->waitForAccess));

	pthread_mutex_unlock(&(flptr->mutex));
}

/**
 * end file access
 * @param flptr fileaccess pointer
 * @param id thread id
 */
void endAccess(FileAccessPtr flptr, int id)
{
	pthread_mutex_lock(&(flptr->mutex));

	flptr->sum -= id ;
	pthread_cond_broadcast(&(flptr->waitForAccess));
	printf("Thread %d ending file access\n", id);
	pthread_mutex_unlock(&(flptr->mutex));
}
