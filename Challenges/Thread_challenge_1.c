#include <stdio.h>
#include <pthread.h>

//c
#define NTHREADS 10
void *threadFunc(void *val);
int counter = 0;

int main()
{
    /*
    for (int i = 0; i < 10; i++)
    {
        pthread_t thread[i];

        pthread_create(&thread[i], NULL, (void *)threadFunc, (void *)i);

        pthread_join(thread[i], NULL);
    }
    */

    //for (int k = 0; k < 150; k++)
    //{

    //c
    pthread_t thread_id[NTHREADS];
    int values[NTHREADS];

    //c
    for (int i = 0; i < NTHREADS; i++)
    {
        values[i] = i;
        pthread_create(&thread_id, NULL, (void *)threadFunc, &values[i]);
    }

    //c
    for (int i = 0; i < NTHREADS; i++)
    {
        pthread_join(thread_id[i], NULL);
        pthread_exit(&thread_id[i]);
    }
    counter = 0;

    // }

    return 0;
}

void *threadFunc(void *val)
{
    int *x = (int *)val; // casting the data we get to an int

    counter++;

    printf(" The passed value %d : thread ID : %li .... counter : %d\n", *x, pthread_self(), counter);
    printf(" The passed value %d : thread ID : %li .... counter : %d\n", *x, pthread_self(), counter);

    return NULL;
}