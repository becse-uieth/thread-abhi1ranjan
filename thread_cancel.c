#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
#include<pthread.h>
#include<unistd.h>

void *thread_func() {
	int o_state,i=0;
	printf("Entered secondary thread\n");
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,&o_state);
	while (1) {
    		printf("Secondary thread is looping\n");
    		pthread_testcancel();
    		sleep(1);
    		if (++i == 5) {
      /* Since default cancel type is deferred, changing the state will allow the next cancellation point to cancel the thread */
        		printf("Cancel state set to ENABLE\n");
        		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        	}
        } 
  return NULL;
}

/*	sleep(60);
	pthread_setcancelstate(o_state,NULL);
}*/

int main()
{
	pthread_t tid;
	int r=0;

  	printf("Entering testcase\n");

  	/* Create a thread using default attributes */
  	r = pthread_create(&tid, NULL,&thread_func, NULL);
	if(r == -1) {
		printf("Error creating thread\n");
		abort();
	} 
  	sleep(10);

  	printf("Cancel the thread\n");
  	r = pthread_cancel(tid);
	if(r == -1) {
		printf("Error while cancellation\n");
		abort();
	} 
	
  sleep(5);
  printf("Main completed\n");
  return 0;

}
