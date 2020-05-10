#include <stdio.h>
#include <pthread.h>

void *hello_func()
{
    printf("Hello world.. \n");
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread = 0;
    pthread_create(&thread, NULL, hello_func, NULL);
    pthread_join(thread, NULL);
    pthread_exit(NULL);

    return 0;
}