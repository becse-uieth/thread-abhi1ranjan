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
	int c;
	int k;
	pthread_t tid;
	int a[2]={2,3};
	k=pthread_create(&tid,NULL,&add,&a);
	k=pthread_join(tid,(void *)&c);
	int *d;
	d=(int *)c;
	printf("%d",d);
	return 0;
}

