#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];

void* doSomeThing(void *arg)
{
    unsigned long sum, i = 0;
    sum=0;
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing AND thread id=%lu \n",id);
    }
    else
    {
        printf("\n Second thread processing AND thread id=%lu \n",id);
    }

    for(i=0; i<100;i++)
    {
	sum=sum+i;
	printf("Sum=%lu \n",sum);
    }
    return NULL;
}

int main()
{
    int i = 0;
    int err;

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");

        i++;
    }

    sleep(5);
    return 0;
}
