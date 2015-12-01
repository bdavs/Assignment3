#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

typedef struct
{
int value;
}	shared_mem; shared_mem	*counter;
/* This fcn should increase the value of the shared variable "counter" all the way
up to 50000 */

process1()
{

}

/* This fcn should also increase the value of the shared memory variable "counter" all the way
up to 50000 */

process2()
{

}

/*	The Main Body	*/

main()
{



memory */


key_t	key = IPC_PRIVATE;	/* shared memory key */ int	shmid;	/* shared memory ID */ shared_mem	*shmat1;	/* function to allocate shared

int	pid1;	/* process id for child1 */
int	pid2;	/* process id for child2 */


/* attempts to attach to an existing memory segment	*/

if (( shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < 0)
{
perror("shmget"); exit(1);
}

/*attempts the shared memory segment	*/

if((counter = (shared_mem *)shmat(shmid, NULL, 0)) == (shared_mem *) -1)
{
perror("shmat"); exit(1);
}

/*initializing shared memory to 0 */ counter->value = 0;


/* fork process one here */

/* fork process two here */

/* parent waits (use wait();) for child processes to finish.
*/

/* parent process reports value of counter */

/* parent process exits safely */

/*deallocate shared memory */
if(shmctl(shmid, IPC_RMID, (struct shmid_ds *)0)== -1){ perror("shmctl");
exit(-1);
}
exit(0);

}
