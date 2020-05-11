/*...condition variables....*/

#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10

pthread_mutex_t lock;
pthread_mutex_t condition_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t even_done = PTHREAD_COND_INITIALIZER; //creating a condinal variable

int num_evens_fin = 0; //to indicate when finish devideing the numbers
void *threadFunc(void *val);
int counter = 0;

int main()
{
    //for (int k = 0; k < 150; k++)
    //{

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
    sleep(1); // this is to give time to create all the threads,
              // if we signal without sleep there might be a thread that is still not created so there will be a deadlock.
              // now :all odd threads are created and waiting

    while (1) //until all the even threads complete
    {
        if (num_evens_fin == NTHREADS / 2)
        {
            pthread_cond_broadcast(&even_done); // broadcast the signal to all the waiting threads
            break;
        }
    }

    for (int i = 0; i < NTHREADS; i++)
    {
        pthread_join(thread_id[i], NULL);
        pthread_exit(&thread_id[i]);
    }
    //counter = 0;
    //num_evens_fin = 0;
    //}

    return 0;
}

void *threadFunc(void *val)
{

    int *x = (int *)val; // casting the data we get to an int --- this a local variable so each thread has its own

    pthread_mutex_lock(&lock);
    //pthread_mutex_lock(&condition_lock);  ---- another method

    if (*x % 2 == 0) //even
    {
        num_evens_fin++;
    }
    else
    {
        pthread_cond_wait(&even_done, &lock);
        /*
        if this is a odd no thread, it should wait.
        1. pointer to the condition variable
        2. pointer to the lock (here the thread should sleep while it gets the chance but, the thread releases the lock when sleeps,
            so when the thread wakes it should have the lock it had when it goes to sleep.)
        */
    }

    //pthread_mutex_unlock(&condition_lock);    ---- another method

    //pthread_mutex_lock(&lock);    ---- another method

    counter++;
    printf(" The passed value %d : thread ID : %li .... counter : %d\n", *x, pthread_self(), counter);
    printf(" The passed value %d : thread ID : %li .... counter : %d\n", *x, pthread_self(), counter);

    pthread_mutex_unlock(&lock);

    return 0;
}