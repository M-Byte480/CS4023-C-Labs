#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

const long DEFAULT_NUM_THREADS = 50;
pthread_mutex_t lock; // Declare lock

void* PrintHello(void* threadid)
{
    long tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    printf("  Part 2 of the message from thread #%ld!\n", tid);
    pthread_mutex_unlock(&lock); // Unlock currently running thread
    pthread_exit(NULL);

}

int main(int argc, char* argv[])
{
    pthread_mutex_init(&lock, NULL); // Initialize lock
    long num_threads = DEFAULT_NUM_THREADS;
    if (argc > 1) {
        num_threads = atol(argv[1]); // Override num_threads if specified as an argument
    }

    pthread_t threads[num_threads];
    pthread_mutex_init(&lock, NULL);
    for (long t=0; t < num_threads; t++)
    {
        pthread_mutex_lock(&lock); // Lock currently running thread

        printf("In main: creating thread %ld\n", t);
        int result = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (result) {
            printf("ERROR; return code from pthread_create() is %d\n", result);
            exit(-1);
        }
    }

    pthread_mutex_destroy(&lock); // delete lock
    /* Last thing that main() should do */
    pthread_exit(NULL);
}

