#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define COUNT 1000000
pthread_mutex_t g_mutext_lock;
int i = 0;


void *thread_1_routine(void *arg)
{
    int j = 0;

    for (j = 0; j < COUNT; j++)
    {
        pthread_mutex_lock(&g_mutext_lock);
        i++;
        printf("thread1: i = %d\n", i);
        pthread_mutex_unlock(&g_mutext_lock);
    }
}

int main(int argc, char const *argv[])
{
    pthread_t thread1;
    pthread_t thread2;

    pthread_mutex_init(&g_mutext_lock, NULL);
    pthread_create(&thread1, NULL, thread_1_routine, NULL);
    pthread_create(&thread2, NULL, thread_1_routine, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&g_mutext_lock);

    return 0;
}


