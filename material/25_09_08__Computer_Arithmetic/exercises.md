# Exercises

Helpful tool: https://evanw.github.io/float-toy/

## What to Learn From This Exercise
This sort of extremely low level math would never be done manually by you, 
this is entirely handled by compilers and the computer itself. Don't worry if
it takes a while to work out by hand your way through them as the difficulty 
of doing this by hand is part of the point of this exercise. Secondly, this
sort of low level knowledge about what is actually going on under-the-hood of
a higher level language is important for your understanding. 

As we go forward through the course, you'll keep coming back to these problems
as we write data to files, networks etc and read it unknowingly in a different
format. Hopefully from this exercise you can get an idea of some different ways
of expressing the same data so can recognise it in debug messages in future 
when things are behaving as expected.

## From COD

* 3.1

* 3.3

* 3.20 (the typesetting is terrible here; what appears to be a
multiplication is supposed to read `0x0C000000`).

* 3.22 (the typesetting is terrible here; what appears to be a
multiplication is supposed to read `0x0C000000`)

* 3.23

* 3.24

* 3.27

<details>
<summary>Open this to see the answer</summary>

* Binary fraction: -0.00101 * 2⁰

* Normalised binary fraction: -1.01 * 2-³

* Sign bit (S): 1

* Binary significand (M): 1.01

* Binary frac: 0100000000

* E: -3

* Exp: E + Bias = -3 + 15 = 12 = (binary) 01100

* Total: S Exp Frac = 1 01100 0100000000

</details>

## More number conversion

Play the [IEEE 754
game](https://topps.diku.dk/compsys/floating-point.html) until you
think you understand floating point numbers.

## Radix-sorting numbers

[Radix sort](https://en.wikipedia.org/wiki/Radix_sort) is a
non-comparison-based sorting algorithm that is often more efficient
than comparison-based algorithms like Quicksort.  In its simplest
form, it sorts by decomposing elements into bits, and then sorting one
bit at a time.  This sorts
[lexicographically](https://en.wikipedia.org/wiki/Lexicographic_order)
(with `0 < 1`).  For some values, the lexicographic ordering is not
the same as our intuitive sort ordering.  For example, consider a
lexicographic comparison of the two bit sequences

* *x*: `11111111`
* *y*: `00000000`

Lexicographically, the ordering is `y < x`.  If these bit sequences
are interpreted as 8-bit unsigned integers, this means `0 < 255`,
which matches the usual ordering.  However, if these sequences are
interpreted as 8-bit *signed* integers in two's complement,
lexicographic ordering gives us `0 < -128`, which is likely not
desirable.

Now consider and answer the following:

1) How can we transform the bits of two's complement signed integers
such that they can be compared lexicographically?

<details>
<summary>Open this to see the answer</summary>

Flip the most significant bit.

</details>

2) How can we transform the bits of IEEE 754 floating point numbers
such that they can be compared lexicographically?

<details>
<summary>Open this to see the answer</summary>

Flip the sign bit, *and* if the sign bit is set, flip all other bits.

</details>
