# Exercises

## What to Learn From This Exercise
Today we're building from scratch a system _similar_ to the one in A2. It 
should hopefully give you some practice in assembling concurrent systems, as 
well as how to keep them correct. LLMs, Google and stackoverflow might be of 
help guiding you on what functions and techniques you can use through your 
system but they are TERRIBLE at higher level design avoiding race conditions 
and deadlocks. Be very sure to double check and test these things yourself.

## Task 1: Concurrent Execution
Write a short program that takes a command line argument for the number of 
threads to execute concurrently. You should start that many threads 
concurrently. Confirm that each thread has indeed executed concurrently by 
giving them some task (such as just sleeping) that takes enough time that you
can see them all starting 'at once' and overlapping their computation. All
threads should be defined in the same function.

**Hint: The easiest way to see that processes are operating at the same time is
by getting them to print when they start and when they are done. If these are
interleaved, then concurrency must have occurred.

**Hint: You'll need some way to uniquely identify each process so you can see 
how each one performs. Giving each thread a unique ID or name would be a good
idea here.

The following sub-headings will give some guidance and hints on how you can do 
this. Try and get started without too much help first, and read the relevant 
section if you get stuck.

### Defining a thread
Remember a thread is defined within a function of the form:

    void* XXXX(void* XXXX) {}

with XXXX representing some descriptive function and variable names. You can 
then manage this thread with the pthread functions, so remember to include:

    #include <pthread.h>

in your code. You can see the documentation for pthreads [here](https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html)

### Running a thread
Threads are started with the _pthread_create(...)_ function which has 
arguments as shown: 

    int pthread_create(pthread_t thread,
                       const pthread_attr_t attr,
                       typeof(void *(void *)) *start_routine,
                       void arg);

That is, it takes a pointer to a place to put a thread id, some flags to alter
its behaviour, the actual function to run as a thread, and then a pointer to
any input arguments. 

Setting up the _thread_ id pointer just means we need to create a pthread_t 
pointer, or an array of several if we are going to start many threads. These
are actually populated by the pthread_create function, to give us a set of IDs
of started threads so we can check up on them or issue commands such as to stop

The _attr_ would let us set specific attributes on how this thread should
operate. We can just set it to NULL though to use the default attributes. If 
you're especially interested in what attributes you could set then consult
[here](https://man7.org/linux/man-pages/man7/attributes.7.html), but this is 
by no means a necessity.

The _start_rountine_ just points to the function that wants to be run as a 
thread

Finally the _arg_ is a single pointer to the arguments used within the thread.
Keep in mind that as a single pointer, if you wish to pass multiple arguments
then you will need to bundle them together into a single struct and pass that.

### Thread managements
Any threads started must be managed! Usually that means that we manually stop
them with the command:

    pthread_cancel()

or waiting on a thread to stop with the command:

    pthread_join()

If we don't use these then we're leaving our system with lots of dangling 
threads. OK the OS will eventually automatically clean these up for us, but it 
is a lot more efficient for us to clean them up ourselves rather than 
depending on the blunt hammer of the OS.

### Passing arguments to the threads
In order to pass any arguments to the threads you will need to use a single 
pointer. Depending on how you implement your solution, you might need only a 
single argument, but I think it is a good idea to pass more than one. For 
instance you probably need a unique ID for each thread, and you might as well
throw in a configurable time to go to sleep for as well. I ended up with a
struct like this:

    struct thread_args {
        int id;         // ID of the thread
        int naptime;    // How long it sleeps for
    };

Each thread should have its own instance of the struct created and passed to 
its thread. You need to make sure you aren't reusing the same struct as that
will introduce race conditions! The struct is passed to the thread as a void*
so you'll also need to cast it back to the original struct within the thread 
to access any attributes within.

## Task 2: Accessing shared resources
Write a short program that starts a number of counter threads, each of which
will increment a shared integer a number of times. E.g. each of N counter 
threads should perform add 1 to a shared integer M times resulting in the 
integer being MxN. The number of counter threads to start, and the amount of 
increments each counter will perform should both be given by command line 
arguments and passed to the counter threads. 

Note that obviously task 1 may inspire a lot of this implementation, but you
will probably have to alter some of what you implemented, as well as adding 
new variables and functions.

### Race conditions
The big change from task 1 is you now need to manage your race conditions on 
a shared variable. Be sure to test your implementation with suitably large 
amounts of counting to let the threads really interleave their execution. Also
note that as we're doing some very simple calculations that most compilers
will optimise away, you should make sure to turn off the compiler 
optimisations. This is done by ensuring you pass the '-O0' flag to your 
compiler in your makefile

### Mutexes
Avoiding a race can be easily achieved through the use of mutexes. Remember 
that any time you lock a mutex, you MUST unlock it at some point or else you
will introduce deadlock e.g. no one can progress. A good rule of thumb it that
as soon as you lock, immediately do whatever work is necessary to be in the
lock, and then release it as soon as you're done.

## Task 3: Pushing to a shared list
Write a short program that starts a number of producer threads, each of which
will add a number of entries to a shared queue. E.g. each of N producer threads
should add M many entries to a queue resulting in a queue of MxN entries. The 
number of producer threads to start, and the amount of entries each producer 
will produce should both be given by command line arguments and passed to the 
producer threads. The contents of the entries is not especially important 
here, but it should be a struct. You could give each entry an ID, a name, or 
some meaningless data, as long as you are adding a struct to a queue.

Note that obviously task 1 and 2 may inspire a lot of this implementation, but 
you will probably have to alter some of what you implemented, as well as adding
new variables and functions.

### Defining a queue
Start by defining a struct to contain your queue. It should include some sort 
of buffer to store in the data, along with some way of tracking how much data 
is being stored. You may also need some form of locking to prevent race 
conditions. I settled on the below as a structure:

    struct queue {
        int total_capacity;     // how large our currently allocated queue is
        int current_capacity;   // how much data we're actually storing
        struct job **queue;     // queue to actually store our data
        pthread_mutex_t mutex;  // lock to ensure no races
    };

This struct will be used to define a variable length queue, so we allocate 
some area of data which we will track with queue. We track the amount of data
allocated using the total capacity and how much is actually used using 
current capacity.

### Initialising the queue
The shared queue struct will need to be initialised. This is just a matter of
setting up any attributes defined by your queue struct to a sensible starting
value. e.g. setting a tracker for how many elements you have to an initial 
value of 0.

### Pushing to the queue
Any producer thread should call a function to push to the queue. This will consist of taking a queue and job as function inputs, with the function then inserting that job into the queue. Some attributes within the queue such as its current capacity will then be appropriately updated. If the queue is not large enough to accommodate the to be added job, then it is expanded to fit it.
As many different producers could call at the same time it is up to this function to ensure no race conditions occur. You should therefore consider adding a lock, and how much or little of your push function needs to be locked.

### Freeing memory
Remember that whenever you allocate memory you should free it. Make sure that 
if you allocate any data within implementation that you also free it.

