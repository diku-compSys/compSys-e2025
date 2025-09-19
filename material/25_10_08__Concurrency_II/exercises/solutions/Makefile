CC=gcc
CFLAGS=-Wall -Wextra -pedantic -pthread -O0 -g3
PROGRAMS=task_one task_two task_three

all: $(PROGRAMS)

%: %.c
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(PROGRAMS)
