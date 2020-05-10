#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock1, lock2; //creating mutex

void *resource1()
{
    pthread_mutex_lock(&lock1); /* useing the mutex lock 1 to control access */

    printf("Job started in resource 1..\n");
    sleep(2);

    printf("trying to get resourece 2..\n");

    //pthread_mutex_lock(&lock2); /* useing the mutex lock 2 to control access */ -- this will result in a deadlock
    while (pthread_mutex_trylock(&lock2)) //tries to lock
    {
        pthread_mutex_unlock(&lock1); // while tring to lock &lock2 unlock &lock1 so otherthreads can access so there wont be a deadlock.
        sleep(2);
        pthread_mutex_lock(&lock1);
    }

    printf("Acquired resource 2\n");
    sleep(2);

    pthread_mutex_unlock(&lock2); /* releasing lock 2 */

    printf("job finished using resource 1..\n");

    pthread_mutex_unlock(&lock1); /* releasing lock 1 */

    pthread_exit(NULL);
}

void *resource2()
{
    pthread_mutex_lock(&lock2);

    printf("Job starting in resource 2...\n");
    sleep(2);

    printf("trying to get resource 1 .. \n");

    pthread_mutex_lock(&lock1);
    printf("Acquired rescourse 1..\n");
    sleep(2);

    pthread_mutex_unlock(&lock1);

    printf("finished using resource 1..\n");

    pthread_mutex_unlock(&lock2);

    pthread_exit(NULL);
}

int main()
{

    pthread_mutex_init(&lock1, NULL); //dynamically initialising the mutex
    pthread_mutex_init(&lock2, NULL); //dynamically initialising the mutex

    pthread_t t1, t2;

    pthread_create(&t1, NULL, (void *)resource1, NULL);
    pthread_create(&t2, NULL, (void *)resource2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}