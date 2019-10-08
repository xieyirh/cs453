#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

int check_if_sorted(long n);
void generate_random_array(long n, int seed);
void* thread_mergesort(void *param); 
void single_mergesort(void *param);
void merge(long p, long q, long r);
void insertion_sort(long p, long r);
double getMilliSeconds();


/*
 * generate_random_array(int A[], int n, int seed):
 *
 * description: Generate random integers in the range [0,RANGE]
 *              and store in A[1..n]
 */

#define RANGE 1000000
#define TRUE 1
#define FALSE 0

extern int thread_count;
extern int  max_thread;

long *A;
typedef struct index{
    long p;
    long r;
} pair;
