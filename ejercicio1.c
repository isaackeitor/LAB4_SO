#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* process1(void* arg)
{
    while(1)
    {   
        printf("Process 1 is trying to acquire resource 1\n");
        pthread_mutex_lock(&mutex1);
        printf("Process 1 acquired resource 1\n");

        printf("Process 1 is trying to acquire resource 2\n");
        pthread_mutex_lock(&mutex2);
        printf("Process 1 acquired resource 2\n");

        // Simulate processing
        printf("Process 1 is processing...\n");
        sleep(1); // Sleep for a second to simulate processing time
        printf("Process 1 has finished processing\n");

        pthread_mutex_unlock(&mutex2);
        pthread_mutex_unlock(&mutex1);
        
    }
    return NULL;
}

void* process2(void* arg)
{
    while(1)
    {
        printf("Process 2 is trying to acquire resource 2\n");
        pthread_mutex_lock(&mutex2);
        printf("Process 2 acquired resource 2\n");

        printf("Process 2 is trying to acquire resource 1\n");
        pthread_mutex_lock(&mutex1);
        printf("Process 2 acquired resource 1\n");

        // Simulate processing
        printf("Process 2 is processing...\n");
        sleep(1); // Sleep for a second to simulate processing time
        printf("Process 2 has finished processing\n");

        pthread_mutex_unlock(&mutex1);
        pthread_mutex_unlock(&mutex2);
        
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, process1, NULL);
    pthread_create(&thread2, NULL, process2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    return 0;
}