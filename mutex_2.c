#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 

pthread_t tid[2]; 
int counter=10; 
pthread_mutex_t lock; 

void* increase(void* arg) 
{ 
    pthread_mutex_lock(&lock); 

	unsigned long i = 0;  
	printf("\n Job %d has started\n", counter); 
	for (i = 0; i < 100000; i++) {
		counter = counter + 1;
	}
	printf("\n Job %d has finished\n", counter); 

	pthread_mutex_unlock(&lock); 
	
	return NULL; 
} 

void* decrease(void* arg) 
{ 
	pthread_mutex_lock(&lock); 
	
	unsigned long i = 0; 
	printf("\n Job %d has started\n", counter); 
	for (i = 0; i < 100000; i++) {
		counter = counter - 1;
	}
	printf("\n Job %d has finished\n", counter); 

	pthread_mutex_unlock(&lock);
	
	return NULL; 
} 

int main(void) 
{ 
	int error; 
	error = pthread_create(&(tid[0]), NULL, &increase, NULL); 
	if (error != 0) 
		printf("\nThread can't be created : [%s]", strerror(error)); 
	error = pthread_create(&(tid[1]), NULL, &decrease, NULL); 
	if (error != 0) 
		printf("\nThread can't be created : [%s]", strerror(error));

	pthread_join(tid[0], NULL); 
	pthread_join(tid[1], NULL); 

	return 0; 
} 