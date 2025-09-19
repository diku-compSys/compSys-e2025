#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct thread_args {
    int id;         // ID of the thread
    int naptime;    // How long it sleeps for
};

void* thread(void* p) {
    struct thread_args ta = *(struct thread_args*)p;
    printf("Hello from %d, I'm sleeping for %d\n", ta.id, ta.naptime);
    sleep(ta.naptime);
    printf("Goodbye from %d\n", ta.id);
    return NULL;
}

int main(int argc, char** argv) {
    assert(argc == 2);  
    int nthreads = atoi(argv[1]);
    pthread_t ptids[nthreads];

    struct thread_args args[nthreads];
    
    for (int i = 0; i < nthreads; i++) {
        args[i].id = i;
        args[i].naptime = 1;
        pthread_create(&ptids[i], NULL, thread, &args[i]);
    }

    for (int i = 0; i < nthreads; i++) {
        pthread_join(ptids[i], NULL);
    }
}