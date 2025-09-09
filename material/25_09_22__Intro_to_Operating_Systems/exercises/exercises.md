# Exercises

## What to Learn From This Exercise
Today we're going to be running a few small investigations on how processes
behave in some potentially unexpected ways. You may be able to answer these
without implementing any code, but its worth running the tasks to check your
intuitions are correct. Here we're beginning to focus more on concepts and 
design rather than just testing your implementation ability. Using LLMs to 
quickly implement some code could be an idea here to get a quick starting 
point, but do make sure that you're actually completing the task at hand. 

You should make a few variations of each task, such as in Question 1 below, try
several variations of updating variables before and after fork, and forking 
different amounts to ensure you really can see the effect of what you're 
implementing.

## From [OSTEP chapter 5](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf)

Homework (Code) (p. 14)
* Question 1
* Question 2 (but feel free to use `fopen()` instead of `open()`)
* Question 3
* Question 5
* Question 6

## A1 Prep
As preparation for A1, we're going to have a go at implementing some functions 
used in A1. The purpose here is to get some familiarity with what is going on
in the handed out code and greater understanding of the system. You may also
be able to adapt some of this code for your implementations

### record.h
Look through the record.h file. This only does 2 significant things. Firstly
it declares a ´record´ struct and then it provides a signature for the 
´read_records´ and 'free_records' functions. You shouldn't need to alter 
either of these for this task, but do look closely at the ´record´ struct. It
shows all the attributes for each location in our database. Note that we're
using a reduced database from that used in A1 so there are fewer attributes 
here. You can see the data we're using for this exercise in ´100_ids.tsv´

### record.c
This file sets out our implemenation for reading in all the records in the
'read_records' function. This then calls the 'read_record' function to 
process each line one at a time. Currently it is not processing most of the 
attributes in a record. It's up to you to implement these so that the file is
read and processesed correctly.

### test_implementation.c
There is a simple test file provided, which runs a few very basic tests for 
the following tasks. These tests are by no means exhaustive so you might
wish to expand them to be sure that you're definitely solving things. You
can run this file by running:

    ./test_implementation 100:ids.tsv

All of the following tasks should only involve altering the 'read_record'
function in 'record.c'. Once they are both finished you should see no errors
reported by the 'test_implementation' program.

## Task 1

Modify record.c so that is does not read the data header into your records

## Task 2

Modify record.c so that it reads in all of the attributes in the record 
struct correctly 