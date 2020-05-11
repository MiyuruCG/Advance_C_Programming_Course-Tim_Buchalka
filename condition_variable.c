#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;     // this is the lock for the critical section
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER; // this is the lock for the condition variable wait.
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;    // creating the condition variable.

void *functionCount1();
void *functionCount2();
int count = 0; //global variable

#define COUNT_DONE 10
#define COUNT_HALT1 3
#define COUNT_HALT2 6

int main()
{
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &functionCount1, NULL);
    pthread_create(&thread2, NULL, &functionCount2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

void *functionCount1()
{
    for (;;)
    {
        pthread_mutex_lock(&condition_mutex); //mutex lock for the condition variable

        while (count >= COUNT_HALT1 && count <= COUNT_HALT2)
        {
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }

        pthread_mutex_unlock(&condition_mutex); // unlock condition variable

        pthread_mutex_lock(&count_mutex); //lock shared variable

        count++;
        printf("Counter updated , function 1 :..%d\n", count);

        pthread_mutex_unlock(&count_mutex); //unlock shared variable

        if (count >= COUNT_DONE)
        {
            return NULL;
        }
    }
}

void *functionCount2()
{
    for (;;)
    {
        pthread_mutex_lock(&condition_mutex);

        if (count < COUNT_HALT1 || count > COUNT_HALT2)
        {
            pthread_cond_signal(&condition_cond);
        }

        pthread_mutex_unlock(&condition_mutex);

        pthread_mutex_lock(&count_mutex);

        count++;
        printf("counter updated .. function 2 : %d\n", count);

        pthread_mutex_unlock(&count_mutex);

        if (count >= COUNT_DONE)
        {
            return NULL;
        }
    }
}