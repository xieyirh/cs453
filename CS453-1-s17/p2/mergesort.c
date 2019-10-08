#include "mergesort.h"

const int INSERTION_SORT_CUTOFF = 100; //based on trial and error

/*
 * insertion_sort(int A[], int p, int r):
 *
 * description: Sort the section of the array A[p..r].
 */
void insertion_sort(long p, long r) 
{
	int j;

	for (j=p+1; j<=r; j++) {
		int key = A[j];
		int i = j-1;
		while ((i > p-1) && (A[i] > key)) {	
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}

/*
 * serial_mergesort(long p, long r):
 *
 * description: Sort the section of the array A[p..r].
 */
void serial_mergesort(void *param) 
{

    pair *pr = (pair *)param;
    long p = pr->p;
    long r = pr->r;
    long q =(p + r)/2;
    pair param1, param2;

    if (r-p+1 <= INSERTION_SORT_CUTOFF)  {
	insertion_sort(p,r);
    } else {
        param1.p = p;
        param1.r = q;

        param2.p = q + 1;
        param2.r = r;

	serial_mergesort(&param1);
	serial_mergesort(&param2);
        merge(p, q, r);
    }
}
		

/*
 * serial_mergesort(int A[], int p, int r):
 *
 * description: Sort the section of the array A[p..r].
 */
void* thread_mergesort(void *param) 
{
	int left_thread_ret, right_thread_ret;
        pthread_t left_thread, right_thread;
        pair *pr = (pair*) param;
        long p = pr->p;
        long r = pr->r;
        long q = (p + r)/2;
        pair param1, param2;


        if (p == r)
	    pthread_exit(0);
	if (thread_count <= max_thread/2) {

            param1.p = p;
            param1.r = q;
            param2.p = q + 1;
            param2.r = r;

            left_thread_ret = pthread_create(&left_thread, NULL, thread_mergesort, (void *)&param1);
            if(left_thread_ret > 0) 
                printf("thread create failed\n");
            else {
                thread_count++;
                printf("the %dth thread created \n",thread_count);
            }

            right_thread_ret = pthread_create(&right_thread, NULL, thread_mergesort, (void *)&param2);
            if(right_thread_ret > 0) 
                printf("thread create failed\n");
            else {
                thread_count++;
                printf("the %dth thread created \n",thread_count);
            }

            pthread_join(left_thread,NULL);
            pthread_join(right_thread,NULL);

	} else {
            serial_mergesort(&param1);
            serial_mergesort(&param2);
        }
        
	merge(p, q, r);
        pthread_exit(0);
        return NULL;

}



/*
 * merge(int p, int q, int r):
 *
 * description: Merge two sorted sequences A[p..q] and A[q+1..r] 
 *              and place merged output back in array A. Uses extra
 *              space proportional to A[p..r].
 */     
void merge(long p, long q, long r) 
{       long *B = (long *)malloc(sizeof(long) *(r-p+1));
	int i = p;
	int j = q + 1;
	int k = 0;
	int l;
		
	// as long as both lists have unexamined elements
	// this loop keeps executing.
	while ((i <= q) && (j <= r)) {
		if (A[i] < A[j]) {
			B[k++] = A[i++];
		} else {
			B[k++] = A[j++];
		}
	}
		
	// now only at most one list has unprocessed elements.
		
	if (i <= q) { 
		// copy remaining elements from the first list
		for (l=i; l<=q; l++) {
			B[k] = A[l];
			k++;
		}
	} else {
		// copy remaining elements from the second list
		for (l=j; l<=r; l++) {
			B[k] = A[l];
			k++;
		}
	}
		
	// copy merged output from array B back to array A
        k = 0;
	for (l=p; l<=r; l++) {
		A[l] = B[k];
	}
        free(B);

}

