CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=gnu99 -g
LDFLAGS=-lm
PROGRAMS=test_implementation record
TESTS=..

.PHONY: all test clean ../src.zip

all: $(PROGRAMS)

test_implementation: test_implementation.o record.o
	gcc -o $@ $^ $(LDFLAGS)

clean:
	rm -rf core *.o $(PROGRAMS)

data:
	wget https://github.com/OSMNames/OSMNames/releases/download/v2.0.4/planet-latest_geonames.tsv.gz
	gunzip planet-latest_geonames.tsv.gz

../src.zip:
	make clean
	cd .. && zip src.zip -r src

.SECONDARY:
