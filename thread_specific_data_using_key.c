#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>

pthread_key_t key;
int count = 0;
pthread_t thread_id;

void wfile() 
{	
	FILE *stream;
	stream= (FILE *) pthread_getspecific(key);
	char  message[] = "this is a thread.";
	fwrite (message, 17, 1, stream);
	fclose(stream);

}

void ffunc() 
{
	FILE *stream;
	stream=(FILE *)pthread_getspecific(key);
//	fclose (stream);
	fflush(stream);
}

void * thread_func() 
{
	count++;
	FILE * stream;
	char filename[100];
	thread_id = pthread_self();
	fprintf (stderr, "%llu\n", thread_id);
	sleep (2);
	sprintf(filename, "file%d.log", count - 1);
	stream = fopen (filename, "w+");
	pthread_setspecific(key, stream);
	wfile();
	ffunc();
//	pthread_exit(NULL);	
}

int main() 
{
	int i;
	pthread_key_create(&key, ffunc);
	pthread_t tid[5];
	for( i=0; i<5; i++) 
	{
		pthread_create ( &tid[i], NULL, &thread_func, NULL);
		pthread_join ( tid[i] , NULL);
	}
  	pthread_key_delete(key);
	return 0;
}

