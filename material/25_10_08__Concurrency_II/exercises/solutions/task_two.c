#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

struct counter_args {
    int id;                 // Unique id for the counter
    int* n;                 // The counter to update
    int counts;             // How many times to count
    pthread_mutex_t* mutex; // lock to ensure no races
};

void* counter(void* p) {
    struct counter_args ca = *(struct counter_args*)p;
    printf("Thread %d starting\n", ca.id);

    for (int i=0; i<ca.counts; i++) {
        pthread_mutex_lock(ca.mutex);
        *ca.n = *ca.n + 1;
        pthread_mutex_unlock(ca.mutex);
    }

    printf("Thread %d done counting\n", ca.id);

    return NULL;
}

int main(int argc, char** argv) {
    assert(argc == 3);  
    int nthreads = atoi(argv[1]);
    pthread_t ptids[nthreads];

    struct counter_args args[nthreads];
    int n = 0;
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    
    for (int i = 0; i < nthreads; i++) {
        args[i].id = i;
        args[i].n = &n;
        args[i].counts = atoi(argv[2]);
        args[i].mutex = &mutex;
        pthread_create(&ptids[i], NULL, counter, &args[i]);
    }

    for (int i = 0; i < nthreads; i++) {
        pthread_join(ptids[i], NULL);
    }

    printf("Final count is: %d\n", n);
}