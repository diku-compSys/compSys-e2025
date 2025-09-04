CFLAGS=-Wall -Wextra -pedantic

all: array 1darray sumrows

clean:
	rm -f mem args

%: %.c
	gcc -o $@ $(CFLAGS) $^
