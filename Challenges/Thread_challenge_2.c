#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
//another method
//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

#define NTHREADS 10
void *threadFunc(void *val);
int counter = 0;

int main()
{
    for (int k = 0; k < 150; k++)
    {

        pthread_t thread_id[NTHREADS];
        int values[NTHREADS];

        if ((pthread_mutex_init(&lock, NULL)) != 0)
        {
            printf("Mutex initialization Failed");
            return 1;
        }

        for (int i = 0; i < NTHREADS; i++)
        {
            values[i] = i;
            pthread_create(&thread_id, NULL, (void *)threadFunc, &values[i]);
        }

        for (int i = 0; i < NTHREADS; i++)
        {
            pthread_join(thread_id[i], NULL);
            // pthread_exit(&thread_id[i]);
        }
        counter = 0;

        counter = 0;
    }

    return 0;
}

void *threadFunc(void *val)
{

    int *x = (int *)val; // casting the data we get to an int

    pthread_mutex_lock(&lock);

    counter++;
    printf(" The passed value %d : thread ID : %li .... counter : %d\n", *x, pthread_self(), counter);
    printf(" The passed value %d : thread ID : %li .... counter : %d\n", *x, pthread_self(), counter);

    pthread_mutex_unlock(&lock);

    return 0;
}