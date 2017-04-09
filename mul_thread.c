#include<stdio.h>
#include<pthread.h>
#include<signal.h>
#include<unistd.h>

void *thread_func() {
	printf("%lu\n",pthread_self());
}


int main() {
	
	int i;
	pthread_t tid[5];
	for( i=0; i<=5; i++) {
		pthread_create(&(tid[i]),NULL,&thread_func,NULL);
		pthread_join(tid[i],NULL);	
	}
}
