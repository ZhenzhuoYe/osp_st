#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int bucket[10]; // the array with 10 slot
pthread_mutex_t mutex;

int in, out = 0;// create the global variable to track the index of producor and consumer (shared by all thread)

//function prototype

void* fillBucket(void* arg);
void* emptyBucket(void* arg);

void* fillBucket(void* arg){
    int num = rand(); // generate the random number
    for(int i = 0; i < 10; i++){
        pthread_mutex_lock(&mutex); // start the lock
        bucket[in] = num;
        printf("value insert into the bucket");
        in = (in+1)%10;// update the in value
        pthread_mutex_unlock(&mutex); // unlock the mutex
    }
    return NULL;

}

void* emptyBucket(void* arg){
    int i;
	for(i = 0; i < 10; i++) {
        pthread_mutex_lock(&mutex); //
        int item = bucket[out];
        printf("present value");
        out = (out+1)%10;
        pthread_mutex_unlock(&mutex); //
    }
	return NULL;

}

int main(){
    pthread_t fill[5]; // define 5 thread for the producor
    pthread_t empty[5]; // define  thread for the consumer

    // create 5 thread for fill
    for (int i = 0; i < 5; i++){
        pthread_create(&fill[i], NULL, (void *)fillBucket, NULL);
    }

    // create 5 thread for empty
    for (int i = 0; i < 5; i++){
        pthread_create(&empty[i], NULL, (void *)emptyBucket, NULL);
    }

    // join the thread
    for(int i = 0; i<5; i++){
        pthread_join(fill[i], NULL);
    }
    for(int i = 0; i<5; i++){
        pthread_join(empty[i], NULL);
    }

    // destory the mutex lock
    pthread_mutex_destroy(&mutex);

    return 0;
}