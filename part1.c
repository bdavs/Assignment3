#include <time.h>
#include <stdio.h>
#include <sys/types.h>
//#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

typedef struct
{
int value;
}	shared_mem; shared_mem	*counter;
/* This fcn should increase the value of the shared variable "counter" all the way
up to 50000 */
int *status;
process1()
{
	printf("Child 1 started. The variable is %d\n",counter->value);
	int i;
	for(i = 0; i<100000;i++){
		counter->value= counter->value +1;
//		printf("%d ",counter->value);
	}
	printf("Child 1 done execution. The variable is %d\n",counter->value);
	exit(0);

}

/* This fcn should also increase the value of the shared memory variable "counter" all the way
up to 50000 */

process2()
{
//	sleep(1);
	printf("Child 2 started. The variable is %d\n",counter->value);
	int j;
	usleep(300);
	 for(j = 0; j<100000;j++){
		counter->value = counter->value +1;
//		printf("%d ",counter->value);
	}
	printf("Child 2 done execution. The variable is %d\n",counter->value);
	exit(0);

}

/*	The Main Body	*/

main()
{



//memory //*/


key_t key = IPC_PRIVATE;	/* shared memory key */ 
int shmid;	/* shared memory ID */ 
shared_mem *shmat1;	/* function to allocate shared*/

int pid1;	/* process id for child1 */
int pid2;	/* process id for child2 */


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
pid1 = fork();
if(pid1 == 0){
	//Im the baby
	process1();
}else{
/* fork process two here */
	 pid2 = fork();
	if(pid2 == 0){
		//I am the second child
//		usleep(100);	
		process2();
	}else{
		/* parent waits (use wait();) for child processes to finish.*/
		wait(&status);
		wait(&status);
		/* parent process reports value of counter */
		printf("The counter variable is: %d\n",counter->value);
		/* parent process exits safely */
		results[k] = counter->value;
		/*deallocate shared memory */
	}
}
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
exit(0);


}
