# Exercises

Welcome to the first exercise class of CompSys. It will introduce some
basic C programming. Work your way through this document and complete
the tasks as you encounter them. Some tasks have hints that you may wish
to consider before you start.

These exercises are intended to give you a first quick feeling of
C. Use the exercise classes to get help.  This is not part of the
mandatory assignments.  Even if you do not manage to solve the
exercises during the classes, they may still be worth working on in
your own time, as they are designed to prepare you for the mandatory
assignments and the exam.

Remember that you can look at the simple programs and files within the 
'lecture_code' directory as inspiration and guidance.

## What to Learn From This Exercise
This exercise is introducing a fundamental write->compile->run interaction
for C programs. You may wish to use aides such as LLMs, Google, or the
course material for more explanation on what these functions are doing but
by the end of this week you will be expected to be able to read and write
simple Makefiles and C programs on your own so do practice doing so without
help where you can.

## Before getting started
This exercise, and course in general will assume you have installed the tools
outlined within the `/tools` directory. Have a look at the README and then the
appropriate file for your system. 

# Write C-programs
C programs are written in files which we then compile into runnable files
called binaries. We often automate this compilation process using a third
file type called a makefile. The first step however is the C file itself.

All C programs start by running the `main` function, which is often written
as `int main(void)`. The `int` part tells us the return type of the function, 
`main` is its name, while `(void)` is where we could provide some input 
parameters but in this case there are none.

C is a very modular language, with most functions defined in additonal files.
For instance, if we wanted to print something to stdout we could use the 
`printf` function which is defined in the `stdio.h` file. Therefore to use 
this function we need to include the `stdio.h` file in our compilation process
or else it will fail.

A simple C file might therefore look something like this:

```
#include <stdio.h>

int main(void) {
  printf("Hello, world!\n");
}
```

## Compile a C-program
To compile a C program we need to call the compiler on the C file. There are
many different C compilers but this course will assume `gcc` as it is commonly
used and broadly works on many different machines. A simple compilation command
could be something like:

```
gcc -o myProgram myProgram.c
```

Typing compilation commands very quickly gets tiring as we add more options 
and files to the command, so we tend to depend on makefiles. These are not C
files themselves, but can be thought of as a way of dynamically creating some 
appropriate bash command lines to run our compilation using the `make` program
to build your programs. To parametrize `make` to build with all the necessary 
compiler flags, start by writing down a `Makefile` containing the following:

```
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra -pedantic -g
```

Then when you add a program `myProgram`, add a rule to `Makefile` as
follows:

```
myProgram: myProgram.c
	$(CC) -o myProgram myProgram.c $(CFLAGS)
```

**Beware**: the leading whitespace *must* be a single tab character.
Now, to compile `myProgram`, just run `make myProgram`. For example:

```
$ make myProgram
```

There are ways to automate parts of this, but we recommend being
explicit until you get a firm grasp on what `make` does.

## Run a C-program
To run the *compiled* program write: 
```
$ ./myProgram
```

## Task 1: Printing in C

Write a C program `mynameis` that prints your name. 

Hint: You may wish to look at `lecture_code/helloworld.c` as particular 
inspiration.

## Arguments in C
Obviously sometimes we wish to run a program with some additional arguments
so we can dictate its behaviour. To read input arguments we need to alter the
main function call to:

```
int main(int argc, char* argv[])
```

This reads in 2 arguments. `argc` (usually referred to as arg c) is the count 
of the number of arguments, while `argv` (referred to as arg v) is an array of
the argument values. 

Note that the actual program name is always the first (e.g. zero-th) argument
so if you called a program with `myProgram A B` then `argc` would be 3, with 
`argV[0]` being myProgram, `argV[1]` being A and `argV[2]` being B.

## Task 2: Input arguments in C

Write a C program `repeatme` that given a string as argument, prints
the string twice on separate lines.

If the program gets a number of arguments that is different from 1 it
should print "`Wrong number of arguments`".

## Task 3: Input argument validation

Write a C program `noAs` that given a string as argument, does either
of the following.

  * If the first character of the string is the `char` `A` it
    prints "`No beginning A's are allowed`",

  * otherwise, it prints the given string.

Hint: strings are arrays in C.

Note: reuse your argument validation from before. You can just as well
learn it from the beginning. _Always sanitise your input._

## Task 4: Guessing game

Write a C program that on startup generates a random number with
`rand()`, and then asks the user to guess it, answering either "too
low" or "too high" when the user guesses wrong.  Take care to handle
non-numeric user input in a sensible way.  _Always sanitise your
input._

## Task 5: Integer representation

Play with integer representation. Try to get `0xA` correct on the different "levels".

http://topps.diku.dk/compsys/integers.html

Next, answer all of the following:

* http://topps.diku.dk/compsys/integers.html#NjdfZmFsc2VfMV8yXzE=
* http://topps.diku.dk/compsys/integers.html#NjFfZmFsc2VfMV8yXzE=
* http://topps.diku.dk/compsys/integers.html#MTAzX2ZhbHNlXzFfMl8x
* http://topps.diku.dk/compsys/integers.html#OTBfZmFsc2VfMV8yXzE=
* http://topps.diku.dk/compsys/integers.html#MjU1X2ZhbHNlXzFfMF8y
* http://topps.diku.dk/compsys/integers.html#MTUzX2ZhbHNlXzFfMF8y
* http://topps.diku.dk/compsys/integers.html#MjE5X2ZhbHNlXzFfMF8x
* http://topps.diku.dk/compsys/integers.html#OTBfZmFsc2VfMV8wXzE=
