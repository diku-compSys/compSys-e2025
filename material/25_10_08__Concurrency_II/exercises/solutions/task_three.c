#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

struct entry {
    int id; // id of producer that made this entry
};

struct queue {
    int total_capacity;     // how large our currently allocated queue is
    int current_capacity;   // how much data we're actually storing
    struct entry **queue;     // queue to actually store our data
    pthread_mutex_t mutex;  // lock to ensure no races
};

struct producer_args {
    int id;                 // Unique id for the counter
    struct queue* queue;    // The queue to add to
    int counts;             // How many times to count
};

void queue_init(struct queue* q, int total_capacity) {
    q->total_capacity = total_capacity;
    q->current_capacity = 0;
    q->queue = calloc(total_capacity, sizeof(struct entry*));
    pthread_mutex_init(&q->mutex, NULL);
}

void queue_push(struct queue* q, struct entry* j) {
    pthread_mutex_lock(&q->mutex);

    if (q->current_capacity == q->total_capacity) {
        q->total_capacity = q->total_capacity * 2;
        q->queue = realloc(q->queue, q->total_capacity * sizeof(struct entry*));
    }

    q->queue[q->current_capacity] = j;
    q->current_capacity += 1;

    pthread_mutex_unlock(&q->mutex);
}

void queue_teardown(struct queue* q) {
    for (int i=0; i<q->current_capacity; i++) {
        free(q->queue[i]);
    }
}

void* producer(void* p) {
    struct producer_args pa = *(struct producer_args*)p;
    printf("Thread %d starting\n", pa.id);

    for (int i=0; i<pa.counts; i++) {
        struct entry* entry = malloc(sizeof(struct entry));
        entry->id =  pa.id;
        queue_push(pa.queue, entry);
    }

    printf("Thread %d done pushing entrys\n", pa.id);

    return NULL;
}

int main(int argc, char** argv) {
    assert(argc == 4);  
    int nthreads = atoi(argv[1]);
    pthread_t ptids[nthreads];

    struct producer_args args[nthreads];
    struct queue q;

    queue_init(&q, atoi(argv[3]));
    
    for (int i = 0; i < nthreads; i++) {
        args[i].id = i;
        args[i].counts = atoi(argv[2]);
        args[i].queue = &q;
        pthread_create(&ptids[i], NULL, producer, &args[i]);
    }

    for (int i = 0; i < nthreads; i++) {
        pthread_join(ptids[i], NULL);
    }

    printf("Final queue size is %d with capacity for %d\n", 
        q.current_capacity, q.total_capacity);
}