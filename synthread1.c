#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>


/* declare a mutex to synchronize access to the standar disply unit */
pthread_mutex_t display_mutex;
/* declare the mutex attributes */
pthread_mutexattr_t display_mutex_attr;


void display(char *str) {

	char *tmp;

	for (tmp=str;*tmp;tmp++)
	{
		write(1,tmp,1);
		usleep(100);
	}
}

void* run(void *params)
{
	char* thread_name;
	int i;

	thread_name = (char*) params;

	/* thread1 will execute the "if" part*/
	if( strcmp(thread_name, "thread1") == 0)
	{
		for(i=0; i<10; i++)
		{
			pthread_mutex_lock(&display_mutex);
			display("Hello World\n");
			pthread_mutex_unlock(&display_mutex);
		}
	}
	else /* thread2 will execute the "else" part*/
	{
		for(i=0; i<10; i++)
		{
			pthread_mutex_lock(&display_mutex);
			display("Bonjour mode\n");
			pthread_mutex_unlock(&display_mutex);
		}
	}
	return NULL;
}


int main() {

	int thread_ret_val;

	/* string names given to both threads */
	char thread1_name[8] = "thread1";
	char thread2_name[8] = "thread2";

	/* declare two threads */
	pthread_t thread1_id, thread2_id;

	/* declare two thread attributes */
	pthread_attr_t th1_attr, th2_attr;


	/* initialize the mutex attributes  */
	/* mutex has been declared globally */
	pthread_mutexattr_init( &display_mutex_attr );

	/* initialize the mutex */
	pthread_mutex_init( &display_mutex, &display_mutex_attr);


	/* initalize attributes of thread1 */
	pthread_attr_init(&th1_attr);

	/* initialize attributes of thread2 */
	pthread_attr_init(&th2_attr);


	/* create thread1 */
	thread_ret_val = pthread_create(&thread1_id, &th1_attr, run, (void*)thread1_name);

	if( thread_ret_val != 0 )
	{
		fprintf(stderr, "failed to create thread\n");
		return 0;
	}

	/* create thread2 */
	thread_ret_val = pthread_create(&thread2_id, &th1_attr, run, (void*)thread2_name);
	if( thread_ret_val != 0 )
	{
		fprintf(stderr, "failed to create thread\n");
		return 0;
	}


	/* main thread will wait for thread1 to finish */
	pthread_join(thread1_id, NULL);

	/* main thread will wait for thread2 to finish */
	pthread_join(thread2_id, NULL);

	/* destroy the display_mutex*/
	pthread_mutex_destroy(&display_mutex);

	return 0;
}
