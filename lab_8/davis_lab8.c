/********************************************************************
 *  Lab 8 Template
 *
 *  Your assignment in this lab is to implement a Semaphore solution
 *  to the critical section problem presented in the template.
 *******************************************************************/

/* Include the necessary header files */
#include <pthread.h>

#include "pv.h"


#define NUMBER 1000000

void *ThreadAdd(void *a);		// Function prototype.

int critical_value; 			// Variable shared between all threads.
int semid;

int main()
{

	// INITIALIZE SEMAPHORE -- TO BE COMPLETED BY YOU
	semun sem_union;
	key_t semkey = ftok("/tmp/cis370-Davis",'t');
	semid = initsem(semkey);

	pthread_t tid_t1;			// Thread 1
	pthread_t tid_t2;			// Thread 2

	pthread_create(&tid_t1, NULL, ThreadAdd, NULL);
	pthread_create(&tid_t2, NULL, ThreadAdd, NULL);

	pthread_join(tid_t1, NULL);
	pthread_join(tid_t2, NULL);

	printf("Both Threads have returned.  Value = %d\n", critical_value);

	// REMOVE SEMAPHORE -- TO BE COMPLETED BY YOU
	semctl(semid,0,IPC_RMID,sem_union);


	return 0;
}

/* This function should allow a thread to increment the critical_value by 1,000,000 */
void *ThreadAdd(void *a)
{
    int i, tmp;
    wait(semid);
    /* Critical Section -- Only one thread should access this at a time! */
    for(i = 0; i < NUMBER; i++)
    {
        tmp = critical_value;     	/* Copy the global count locally */
	 	tmp = tmp+1;       			/* Increment the local copy */
        critical_value = tmp;   	/* Store the local value into the global count */
    }
    signal(semid);
    pthread_exit(0);
}
