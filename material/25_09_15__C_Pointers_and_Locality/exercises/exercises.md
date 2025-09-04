## What to Learn From This Exercise
This exercise should achieve two things. First is a little bit of practice
with pointers and how we can refer to variables in C. Secondly is to practice
using the program GDB to debug your programs when things go wrong. 

Pointers can be very tricky to get your head around so feel free to get some 
further explanation from the course material, your TA, or online. You will 
need to understand how pointers work for the rest of this course so make sure
you understand the distinction between values, pointers and references.

GDB is a very helpful tool for working through what has gone wrong with a 
running program. Other tools are available however so feel free to swap out 
for another debugger if you're having trouble installing it as really we care
that you can debug your running programs effectively, not that you use GDB 
specifically. It can be complex to read all the documentation and guidance for
it, so an LLM might actually be able to summerise some key commands for you. Do 
actually practice their use though.

# Theoretical Exercises

Author: Troels Henriksen <athas@sigkill.dk>

## Pointers

Consider the follow fragments of C programs.  For each program, fill
in the empty underlined spots such that the final value of the
variable `x` is 0.

### 1.

    int x;
    int *p;
    p = &_____;
    *p = _____;

### 2.

    int x;
    int *p;
    int **pp;
    pp = &_____;
    p = &_____;
    **pp = _____;

### 3.

    int x, y;
    int *p = &_____;
    p = _____;
    *p = 0;
    p = _____;
    *p = 1;

### 4.

    int x, y;
    int* arr[2];
    arr[0] = _____;
    arr[1] = arr[0];
    *(arr[1]) = _____;
    *(arr[0]) = *(arr[0]) - 1;

# Practical Exercises

Author: Troels Henriksen <athas@sigkill.dk>

These exercises are intended to give you more experience with C, in
particular with file I/O and simple use of pointers.

The [`solutions`](solutions/) directory contains our solutions.  It's best to 
look at them only when you have tried yourself first, or are stuck.  When
you do look at them, make sure you understand why they work before
moving on.

For the practical programming tasks, you should use make to build your
programs. To parametrize make to build with all the necessary compiler
flags, start by writing down a Makefile containing the following:

  ```
  Makefile
  CC=gcc
  CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
  ```

Then when you add a program `foo`, add a rule to Makefile as follows:

  ```
  Makefile
  foo: foo.c
	$(CC) -o foo foo.c $(CFLAGS)
  ```

Beware: the leading whitespace must be a single tab character. Now, to
compile foo, just run `make foo`. For example:

  ```
  $ make hexabyte
  ```

There are ways to automate parts of this, but we recommend being
explicit until you get a firm grasp on what `make` does.

In the following, we colloquially use "print" as slang for writing to
standard output.

## A hex dumper

Write a C program `hexabyte` that prints in hexadecimal notation the
bytes contained in a file.  For example:

  ```
  $ ./hexabyte ints.bin
  01
  00
  00
  00
  01
  00
  00
  00
  02
  00
  00
  00
  03
  ...
  ```

### Hints

* Define the main function as

  ```C
  int main(int argc, char** argv) {
    ...
  }
  ```

  in order to access command-line parameters (in `argv`).

* Use `fopen(filename, "r")` to open a file for reading.

* Use the `fread()` function to actually perform the read from the
  `FILE*` object.  This function will return `0` when you have read
  the entire file.

* Use `%.2x` format specifier with `printf()` to print an integer as a
  two-digit hexadecimal number.

* Use the `assert` macro from `<assert.h>` to guard against potential
  errors.

## Converting binary integers to ASCII integers

Define a function with the following prototype:

```C
int read_int(FILE *f, int *out);
```

A call `read_int(f, &x)` must read the first four bytes from `f` and
place them in `x`.  If the read succeeds, the function must return 0,
and otherwise 1.

Then write a program `int2ascii.c` such that

```
$ ./int2ascii ints.bin
```

prints, separated by newlines, the numbers from [ints.bin](ints.bin).

### Hints

* Use the `fread()` function to actually perform the read from the
  `FILE*` object.  Remember that you need to read `sizeof(int)` bytes
  at a time (the `size` parameter accepted by `fread()`).

* The return value of `fread()` indicates how many elements were
  succesfully read (and you should read one element in `read_int()`).

## Converting ASCII integers to binary integers

Define a function with the following prototype:

```C
int read_ascii_int(FILE *f, int *out);
```

A call `read_ascii_int(f, &x)` reads an ASCII (text) integer from the
given file, and stores the final integer in `x`.  If the read
succeeds, the function must return 0, and otherwise 1.  Each integer
in the file must be followed by exactly one linebreak character
(`'\n'`), including the last one.  This is exactly the format produced
by `int2ascii`.

Then write a program `ascii2int.c` such that

```
$ ./ascii2int ints.txt ints.bin
```

prints, separated by newlines, the numbers from [ints.txt](ints.txt),
but *also* writes them as raw data to `ints.bin`, with four bytes per
integer.

#### Hints

* The `read_ascii_int()` function is a *parser*, because it translates
  unstructed text data to structured in-memory data.  Parsers are in
  general tricky to write well (and beyond the scope of our course),
  but the algorithm for reading a base-10 integer is fairly
  straightforward:

  1. We are constructing the result in the variable `x`, which is
     initially zero.

  2. Read a single character (byte) from the file.  If this fails,
     then parsing fails.

  3. If the character is a newline (`'\n'`), then parsing is done, and
     `x` is the result.

  4. If the character corresponds to a digit (see below), then convert
     it to the corresponding integer `d` in the range [0,9] and update
     `x`:

     ```
     x = x * 10 + d
     ```

     Then go to step 2.

  5. Else the character is invalid, and then parsing fails.

* To convert an ASCII character `c` corresponding to a digit, to the
  integer representing that digit, do `c - '0'`.  For example,

  ```C
  '7' - '0' == 7
  ```

* To open a file for writing, use `fopen(filename, "w")`.

* To write a raw binary integer `x` to an open file `f`, use
  `fwrite(&x, sizeof(int) 1, f)`.

# Valgrind

## Introduction

Valgrind is a very useful debugging tool for C programs. You can find its
quickstart guide [here](https://valgrind.org/docs/manual/quick-start.html)

The most important thing it does for us is check our memory use. You should run
the program ./exercise_code/traceable_leaks through it using the following
command:

  valgrind ./traceable_leaks

You should find that 5 bytes have been 'definately lost'. This is Valgrind 
saying that we've allocated 5 bytes them without freeing.

We can find which lines are by adding the command line option 
'--leak-check=full' like so:

  valgrind --leak-check=full ./traceable_leaks

This will tell you were you've allocated something you've never freed, but you
will get directed to hexidecimal address. This is actually an index saying 
exactly where you error is, but it is an index within the compiled binary
rather than in something human readable. In order to get something workable
we need to add the '-g' command to the compilation instruction. We can just
add this to our makefile instruction, where we've already set out a CFLAGS 
variable to store all the command line flags we want to add to our runs. Modify
it like so:

  CFLAGS=-pthread -O0 -g

Now when we re make the program and run it through Valgrind once again we will
be told exactly what lines have been allocated but never freed. Note that you
may need to manually deleted the old versions of the runnable binaries to get 
them to be remade if the only thing you've altered is the compiler flag. Add in 
the missing free statements and confirm with valgrind that nothing has gone 
missing. 

## Indirect leaks

Have a look at the file exercise_code/leaks_indirect.c. Run it through valgrind
and observe that there is a distinction between definitely and indirectly lost
memory within it. Definitely lost is like we say before, something allocated 
and that pointer is never freed. Indirectly is essentially the same, but with 
the added fun that we've allocated some memory, with is stored at some pointer
address, but that we've freed the pointer before freeing the memory so even if
we did just try to free it all at the end of our program we would not be able 
to as the program no longer even knows where that allocated memory is stored.

Below the comment within the file, add some code to to free all the memory. 
This will take more than a single line, as you need to free each array entry
manually, then free the pointer to the array. Use valgrind to convince yourself
that you've freed everything you should.

# GDB exercises

Author: Michael Kirkedal Thomsen <kirkedal@acm.org>

The following exercises will to give you some experience with using GDB.

## Play with GDB

Take some of the programs from last weeks exercises or perhaps even
the assignment and play around with GDB. Recreate a bug that you had
in your program and try finding it with GDB. 

For a quick start guide to GDB, you can check out 
[Geeks for geeks guide on GBD](https://www.geeksforgeeks.org/gdb-step-by-step-introduction/). 

We recommend you test most of the
commands on the [GDB QUICK REFERENCE
sheet](https://sourceware.org/gdb/onlinedocs/refcard.pdf)
(which can also be found in today's exercise folder).

## Debug some programs

[Attached](exercise_code/) there is a list of programs containing some
different bugs. Some of them very obvious. Use GDB to identify and
profile the bugs. Record your approach in a GDB script.

We recommend to investigate in the following order:

* `hello.c`
* `table.c`
* `capitalize.c`
* `array.c`
