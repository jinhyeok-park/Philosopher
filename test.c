#include <pthread.h>
#include <stdio.h>

int t = 0;

void    *thread_start(void *i)
{
    (void)i;
    t++;
    return NULL;
}

int main(void)
{
    pthread_mutex_t mut;
    pthread_t       thread;
    pthread_t       thread2;
    pthread_mutex_init(&mut, NULL);
    pthread_create(&thread, NULL, thread_start, NULL);
    pthread_create(&thread2, NULL, thread_start, NULL);
    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);
    printf("%d", t);
}