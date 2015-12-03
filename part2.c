#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SEMPERM  0600
#define TRUE	 	1
#define FALSE    	0
#define NUMBER 1000000

typedef union _semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
} semun;

typedef struct
{
int value;
}	shared_mem; shared_mem	*counter;
/* This fcn should increase the value of the shared variable "counter" all the way
up to 50000 */
int *status;

void processUp();
void processDown();				
int semid;
int initsem(key_t semkey);
int wait(int semid);
int signal(int semid);


int main()
{

	
	key_t key = IPC_PRIVATE;	/* shared memory key */ 
	int shmid;	/* shared memory ID */ 
	shared_mem *shmat1;	/* function to allocate shared*/

	int pid1;	/* process id for child1 */
	int pid2;	/* process id for child2 */
	semun sem_union;
	key_t semkey = ftok("/tmp/cis370-Davis",'t');
	semid = initsem(semkey);

	/* attempts to attach to an existing memory segment	*/

	if (( shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0)
	{
	perror("shmget"); exit(1);
	}

	/*attempts the shared memory segment	*/

	if((counter = (shared_mem *)shmat(shmid, NULL, 0)) == (shared_mem *) -1){
	perror("shmat"); exit(1);
	}
	int results[100];
	int k =0;
	for(k=0;k<100;k++){
	/*initializing shared memory to 0 */ counter->value = 0;


	/* fork process one here */
	pid_t pid;
	for (int i = 1; i <= 6; i++) {
		pid = fork();
		if (pid == -1) {
		    return;
		}
		if (pid == 0 && i%2==0) {
			processUp();
			printf("I am a child: %d PID: %d\n",i, getpid());
		    //sleep (5);
			return;
		}
		if (pid == 0 && i%2!=0) {
			processDown();
			printf("I am a child: %d PID: %d\n",i, getpid());
		    //sleep (5);
			return;
		}	
	}


wait(&status);
		wait(&status);wait(&status);
		wait(&status);wait(&status);
		
			wait(&status);
			/* parent process reports value of counter */
			printf("The counter variable is: %d\n",counter->value);
			/* parent process exits safely */
			results[k] = counter->value;
			/*deallocate shared memory */
		
	
	}
	int exactly=0,lower=0,higher=0;
	for(k=0;k<100;k++){
		if(results[k] == 200000)
			exactly++;
		if(results[k] < 200000)
			lower++;
		if(results[k] > 200000)
			higher++;
	}
	printf("Percentage higher: %d\nPercentage lower: %d\nPercentage exactly: %d\n",higher,lower,exactly);
	if(shmctl(shmid, IPC_RMID, (struct shmid_ds *)0)== -1){ perror("shmctl");
		exit(-1);
	}
	semctl(semid,0,IPC_RMID,sem_union);
	exit(0);



	//return 0;
}

/* This function should allow a thread to increment the critical_value by 1,000,000 */
void processUp()
{
    int i, tmp;
    wait(semid);
    /* Critical Section -- Only one thread should access this at a time! */
    for(i = 0; i < NUMBER; i++)
    {
	counter->value++;
    	/* Copy the global count locally */
   	/* Store the local value into the global count */
    }
    signal(semid);
	exit(0);
    //pthread_exit(0);
}
void processDown()
{
    int i, tmp;
    wait(semid);
    /* Critical Section -- Only one thread should access this at a time! */
    for(i = 0; i < NUMBER; i++)
    {
	counter->value--;
    	/* Copy the global count locally */
   	/* Store the local value into the global count */
    }
    signal(semid);
	exit(0);    
//pthread_exit(0);
}

/* Create and initialize a semaphore with a value of 1 */
int initsem(key_t semkey)
{
	int semid1;
	int status = 0;

	/* Creates a semaphore set containing a single semaphore */
	if((semid1 = semget(semkey, 1, SEMPERM|IPC_CREAT|IPC_EXCL)) == -1)
	{
		if(errno == EEXIST)
			semid1 = semget(semkey, 1, 0);
	}
	else
	{
		semun arg;
		arg.val = 1;

		/* Sets the semval parameter of the semaphore to 1 */
		status = semctl(semid, 0, SETVAL, arg);
	}

	if(semid1 == -1 || status == -1)
	{
		perror("initsem failed");
		return -1;
	}

	/* All okay */
	return(semid1);
}

/* Semaphore wait() procedure */
int wait(int semid)
{
	struct sembuf p_buf;

	// TO BE COMPLETED BY YOU
	p_buf.sem_num = 0;
	p_buf.sem_op = -1;
	p_buf.sem_flg = 0;
	// 1. Set p_buf parameter values
	// 2. Use p_buf to implement the appropriate semaphore operation
	
	semop(semid,&p_buf,1);
	
	return 0;
}

/* Semaphore signal() procedure */
int signal(int semid)
{
	struct sembuf v_buf;

	v_buf.sem_num = 0;
	v_buf.sem_op = 1;
	v_buf.sem_flg = 0;
	// TO BE COMPLETED BY YOU
	// 1. Set v_buf parameter values
	// 2. Use v_buf to implement the appropriate semaphore operation

	semop(semid,&v_buf,1);
	
	return 0;
}

