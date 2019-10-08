
#include "mergesort.h"
/*
 * generate_random_array(int A[], int n, int seed):
 *
 * description: Generate random integers in the range [0,RANGE]
 *              and store in A[1..n]
 */

int thread_count = 0;
int max_thread;

void generate_random_array(long n, int seed)
{
    long i;

	srandom(seed);
    for (i=1; i<=n; i++){
        A[i] = random()%RANGE;
    }

}


/*
 * check_if_sorted(int A[], int n):
 *
 * description: returns TRUE if A[1..n] are sorted in nondecreasing order
 *              otherwise returns FALSE
 */     

int check_if_sorted(long n) 
{
	long i=0;
//        for (i = 1; i <=n; i++)
  //          printf("%ld ", A[i]);
    //    printf("\n");

	for (i=1; i<n; i++) {
		if (A[i] > A[i+1]) {
			return FALSE;
		}
	}
	return TRUE;
}




int main(int argc, char **argv) {

        pthread_t start_thread;
        pair start;


	if (argc < 3) { // there must be at least one command-line argument
			fprintf(stderr, "Usage: %s <input size> <number of threads>  [<seed>] \n", argv[0]);
			exit(1);
	}
	
	long n = atoi(argv[1]);
        max_thread = atoi(argv[2]);

	int seed = 1;
	if (argc == 4)
		seed = atoi(argv[3]);
		
	A = (long *) malloc(sizeof(long) * (n+1)); // n+1 since we are using A[1]..A[n]
	start.p = 1;
        start.r = n;
	// generate random input
	
	generate_random_array(n, seed);
	
	double start_time;
	double sorting_time;

	// sort the input (and time it)
	start_time = getMilliSeconds();
        pthread_create(&start_thread, NULL, thread_mergesort, (void*)&start);
        pthread_join(start_thread, NULL);
	sorting_time = getMilliSeconds() - start_time;
	
	// print results if correctly sorted otherwise cry foul and exit
	if (check_if_sorted(n)) {
		printf("Sorting %ld elements took %4.2lf seconds.\n", n,  sorting_time/1000.0);
	} else { 
		printf("%s: sorting failed!!!!\n", argv[0]);
		exit(EXIT_FAILURE);
	}

        free(A);

	exit(EXIT_SUCCESS); 

}
