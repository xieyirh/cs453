/**
 * FileAccess.h
 *
 * @Since: Mar 9, 2017
 * @Author: yi xie
 */

#ifndef FILEACCESS_H_
#define FILEACCESS_H_

#include <stdlib.h>
#include <pthread.h>

typedef struct fileaccess FileAccess;
typedef struct fileaccess *FileAccessPtr;

struct fileaccess {
	int sum;
	int max;
	pthread_mutex_t mutex;
	pthread_cond_t waitForAccess;
	void (*startAccess) (FileAccessPtr, int);
	void (*endAccess)(FileAccessPtr, int);
};

FileAccessPtr fileaccess_init(int max);


#endif /* FILEACCESS_H_ */
