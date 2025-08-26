#Note turning off optimsations
#CFLAGS=-O0 -fno-tree-vectorize -fno-tree-loop-vectorize -fno-tree-slp-vectorize

CFLAGS=-O0

all: ints floats

clean:
	rm -f ints floats

%: %.c
	gcc -o $@ $(CFLAGS) $^
