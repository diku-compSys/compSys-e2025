# Exercises

## RISC-V

The following exercises will train you in writing more
complicated RISC-V programs.
You will be given pseudocode or C programs, and asked to write similar
programs in RISC-V assembly.

It is up to you to decide how to test them.

You must use [RARS](https://github.com/TheThirdOne/rars) to develop,
test, and run these programs.  [See this guide on using
RARS](../../tools/rars.md).

## What to Learn From This Exercise
At this stage in the course we are not too concerned with your knowledge of 
assembly. Later on a whole section will be given over to computer architecture
and you'll be expected to complete an assignment using assembly, but that is 
not to the end of the course. For now this is mostly to illustrate to you that
underneath all of the concepts and features we will be introducing in the next
few months, what is really taking place are millions of these simple 
manipulations of a small amount of registers. 

I expect that playing around by hand with these problems will be the best way
of illustrating quite how complex even these simple problems can be at this low
level, but you may be able to get the same outcome with tools like LLMs, 
reading, or watching videos.

Additionally, there are some exercises to help you get started on A0. Note that
they're intentionally _similar_ to the tasks in A0 but slightly altered. You 
should be able to use your solutions to these exercises in A0 but may need some
minor alternations to do so. 

### Fibonacci function

Implement the standard recursive definition of the Fibonacci function:

    fib(n) = if n < 2 then 1 else fib(n-1) + fib(n-2)

*Don't* rewrite it to be an iterative loop instead.  Yes, that's more
efficient, but it will not give you experience with function calls in
RISC-V.  Assume that `n` is provided in `a0`, and similarly produce
the result in `a0`.

#### Hints

* See the heavily commented [fact.s](fact.s) program.  Computing
  Fibonacci numbers is very similar.  You should structure your
  implementation the same way (although you don't need to use
  multiplication).

* You will need at least three words of stack space.

### Array equality

The following C function is a simplified version of the standard C
function ``memcmp``:

```C
int memeq(unsigned char *p1, unsigned char *p2, int n) {
  for (int i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return 0;
    }
  }
  return 1;
}
```

It returns 1 if the `n` bytes at `p1` and `p2` are identical, and
otherwise 0.  Recall that C represents *false* as zero and *true* as
non-zero.

Write this function in RISC-V assembly.  Accept `p1`, `p2`, and `n` in
`a0-a2`, and return the result in `a0`.

### Array search

The following C function is a simplified version of the standard C
function `memmem`:

```C
unsigned char* memfind(unsigned char *haystack, int haystacklen,
                       unsigned char *needle, int needlelen) {
  for (int i = 0; i < haystacklen-needlelen; i++) {
    if (memeq(haystack+i,needle,needlelen)) {
      return haystack+i;
    }
  }
  return NULL;
}
```

It tries to find the array `needle` (of length `needlelen`) in the
array `haystack` (of length `haystacklen`).  If it can be found, it
returns the starting address of the match.  Otherwise it returns NULL
(`0`).

Write this function in RISC-V assembly.  Accept parameters in `a0-a3`
and return the result in `a0`.  Use your definition of of `memeq` from
the previous exercise as a helper function.

### Stalin sort

Stalin Sort is a particularly brutal *O(n)* sorting algorithm where
every element that is not in sorted order is simply removed.  We can
implement it in C as such:

```C
int stalinsort(int *array, int n) {
  if (n == 0) {
    return 0;
  }

  int prev = array[0];
  int i = 1;
  for (int j = 1; j < n; j++) {
    if (prev <= array[j]) {
      prev = array[j];
      array[i] = prev;
      i++;
    }
  }
  return i;
}
```

We can't change the size of the array, so instead we move the elements
and return the new size.

Write this function in RISC-V assembly.  Accept parameters in `a0-a1`
and return the result in `a0`.

# A0 Practice
These short exercises should be fairly quick to complete, but should give you
an idea of some quick sanity checks you might wish to carry out in your own 
code. For each of the following tasks, determine if the presented bytes are
valid ASCII, ISO-8859, or UTF-8 as presented in the A0 handout.

Hint: I've intentionally left each question here expressed as hex, rather 
than as the formats given in the assignment, as you're more likely to be able 
to read the byte values as hex if you print them in C, or use GDB. It's far 
less error prone to work out what hex values you expect to see than worry about
printing exactly the data you want in exactly the human readable format you 
want.

Hint: Rather than converting each byte in turn to a readable value for you to
check, can you come up with some ranges of values to make your job easier?

## Theory

### ASCII
Are each of the following valid ASCII files? 

1: 
    0x33, 0x70, 0x3D, 0x78, 0x8B, 0x68, 0x63, 0x5B, 0x37, 0x42

2:
    0x77, 0x47, 0x68, 0x61, 0x3A, 0x7D, 0x65, 0x58, 0x30, 0x74

3:
    0x5D, 0x2A, 0x6E, 0x59, 0x35, 0x3F, 0x3A, 0x4G, 0x63, 0x38

### ISO-8859

1:
    0xDA, 0x2B, 0x31, 0x0E, 0xFC, 0x7C, 0x5C, 0x24, 0xA7, 0xA9

2:
    0x78, 0xE6, 0x3E, 0x3E, 0xAD, 0x43, 0x3C, 0x50, 0x8C, 0xE7

3:
    0x32, 0x9A, 0x70, 0xC1, 0x04, 0xC0, 0x4E, 0xA4, 0x5F, 0xDD

### UTF-8
1:
    0xEB, 0xB5, 0xB2, 0xF5, 0x82, 0x86, 0x9A, 0xF0, 0x88, 0x92, 0xB4, 
    0xCE, 0xBF, 0xF0, 0xA5, 0xAF, 0xB7, 0xE3, 0xB2, 0xAC

2:
    0xD0, 0xBF, 0xE2, 0xAE, 0x8D, 0xF5, 0x90, 0x95, 0x9D, 0xDB, 0x8F, 
    0x56, 0xBB, 0x90, 0xE7, 0xAC, 0x9F, 0xE1, 0x95, 0x90

3:
    0xD1, 0x92, 0xDA, 0x88, 0xD7, 0xAE, 0xC0, 0xBE, 0xE8, 0x80, 0xAA, 
    0x6D, 0xF2, 0xA7, 0x85, 0x82, 0xDD, 0xBC, 0xF6, 0xB1, 0x9A, 0xBE 
  
## Practical

Here we are going to create some simple debugging programs to create some test
data, as well as read it. These aren't strictly necessary for you to complete
A0, but they will help with your development as you start to test your 
solutions. In previous years, most problems students had were caused by testing
on files that did not have the content they thought it had.

### Writing
Take a look at the code in `lecture_code/fwrite-simple.c`. Make a copy of it 
that can write multiple byte values to the same file. Your file should be able
to produce multiple test files for each of the 4 data types. 

Hint: Learn to prioritise what tasks are important. As you're generating static
test data, do you need to accept command line arguments, or can you just 
hardcode some values?

Hint: Think about what data is important to test on. It's usually worth having
a very simple 'first dataset' as a proof of concept, such as a single byte just
to test that your program is working.

### Reading
Take a look at the code in `lecture_code/fread-bytes.c`. Make a copy of it that
can read each of your test files from the writing exercise, and produces a nice
summary of their contents. This sort of debugging is a useful habit to get into
as a way of confirming your test data is indeed what you expect it to be.

Hint: The lecture code file only prints certain values of character, when we 
will want to be able to print anything. 

Hint: Remember to prioritise your tasks. Many characters won't have a pretty
way to be printed but you don't need to figure one out. Just print _something_
that is reflective of the contents so you can debug that you're testing on 
exactly what you think you are.
