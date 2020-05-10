#include <stdio.h>
#include <pthread.h>

void *print_msg_func(void *prt);

int main(void)
{
    pthread_t thread1, thread2;
    char *message1 = "Thread 1 ";
    char *message2 = "Thread 2 ";
    int iret1 = 0, iret2 = 0;

    iret1 = pthread_create(&thread1, NULL, print_msg_func, (void *)message1);
    iret2 = pthread_create(&thread2, NULL, print_msg_func, (void *)message2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("thread 1 returned .... %d \n", iret1);
    printf("thread 2 returned .... %d \n ", iret2);

    pthread_exit(NULL);

    return 0;
}

void *print_msg_func(void *prt)
{
    char *message;
    message = (char *)prt;
    printf("%s \n ", message);

    return 0;
}