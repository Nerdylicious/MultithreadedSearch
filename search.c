/**
 * search.c
 *
 * PURPOSE:		Search an array using threads where each thread searches it's
 *				own portion of the array.
 *
 * TO COMPILE:		gcc -Wall search.c -o prog -lpthread
 * TO RUN:		./prog
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_SIZE 480000

int array[MAX_SIZE];
int NumThreads;
int SearchVal;

enum BOOL{
	false = 0,
	true = 1
};
typedef enum BOOL boolean;	

/**
 * PURPOSE: Each thread searches it's own portion of the array, given by lower_bound
 *          and upper_bound;
 * 
 * INPUT PARAMETERS:
 *		args:		The number of the thread in the range 0 through NumThreads-1
 * 
 * OUTPUT PARAMETERS:
 *		None
 *
 */
void *search(void *args) {

	long MyThreadNum = *(int *)(&args);
	int NumElts = MAX_SIZE/NumThreads;
	int lower_bound = MyThreadNum * NumElts;
	int upper_bound = ((MyThreadNum + 1) * NumElts) - 1;
	int found_position = -1;
	boolean is_found = false;
	//printf("\nlowerbound: %d", lower_bound);
	//printf("\nupperbound: %d", upper_bound);
	
	int i;
	for(i = lower_bound; i <= upper_bound && is_found == false; i ++){
		
		//delay
		int sum=0;
		int k;
		for (k = 0; k < 5000; k ++){
	     	sum += k;
	     }
		if(SearchVal == array[i]){
			is_found = true;
			found_position = i;
		}
	}
	
	if(is_found == true){
		printf("\nThread %ld has found SearchValue %d in position %d\n\n", MyThreadNum, SearchVal, found_position);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[]){

	boolean valid_search_val = false;
	boolean valid_num_threads = false; 
	
	//this if for doing timings only
	/*
	if(argc != 3){
		printf("usage: programname SearchVal NumThreads\n");
		exit(-1);
	}
	SearchVal = atoi(argv[1]);
	NumThreads = atoi(argv[2]);
	*/
	
	int j;
	for(j = 0; j < MAX_SIZE; j ++){
		array[j] = j;
	}
	
	while(valid_search_val == false){
		printf("Please enter the value to search for: ");
		scanf("%d", &SearchVal);
		if(SearchVal < 0 || SearchVal > 479999){
			printf("Please enter a search value between 0 and 479,999\n");
		}
		else{
			valid_search_val = true;
		}
	}
	
	while(valid_num_threads == false){
		printf("Please enter the number of threads to use: ");
		scanf("%d", &NumThreads);
		if(NumThreads != 1 && NumThreads != 2 && NumThreads != 4 && NumThreads != 8){
			printf("Please enter a value of 1, 2, 4 or 8\n");
		}
		else{
			valid_num_threads = true;
		}
	}
	
	pthread_t threads[NumThreads];
	int i;
	int rc;
	long MyThreadNum = 0;
	for(i = 0; i < NumThreads; i ++){
	
		rc = pthread_create(&threads[i], NULL, search, (void *)MyThreadNum);
		MyThreadNum ++;
		if(rc){
			printf("ERROR:rc is %d\n", rc); 
			exit(-1);
      	} 

	}
	for(i = 0; i < NumThreads; i ++){
		
		pthread_join(threads[i], NULL);
	}


	
	
	
	
	
	pthread_exit(NULL);
	return 0;
}























