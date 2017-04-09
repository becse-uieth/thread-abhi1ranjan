#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

//int *sum=0;
void *add(void *a)
{
	int sum=0;
	int *b;
	b=(int *)a;
	sum= *(b+0) + *(b+1);
	return (void *)sum;
}
int main()
{
	int c,l;
	int k;
	pthread_t tid;
	pthread_attr_t attr;
	l=pthread_attr_init( &attr);
	if(l == -1) {
		perror("error in pthread_attr_init");
		exit(1);
	}
	l=pthread_attr_setdetachstate( &attr,PTHREAD_CREATE_DETACHED);
	if(l == -1) {
		perror("error in pthread_attr_setdetachstate");
		exit(2);
	}
	int a[2]={2,3};
	k=pthread_create(&tid,&attr,&add,&a);
	k=pthread_join(tid,(void *)&c);
	if(k!=0){
		printf("Thread not joined\n");
	}
	int *d;
	d=(int *)c;
	printf("%d\n",d);
	return 0;
}

