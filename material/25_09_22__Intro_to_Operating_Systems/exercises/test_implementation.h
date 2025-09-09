// This file (along with its implementation id_query.c) abstracts out
// the user-facing part of the query programs.  It implements the
// following algorithm:
//
// Records <- Read Dataset
// Index <- Produce Index From Records
// While Program Is Running:
//   Read Query From User
//   Lookup Query In Index
// Free Index
//
// Where the specifics of "Produce Index From Records", "Lookup Query
// In Index", and "Free Index" are provided via function pointers.
// This means we can write the main loop just once, and reuse it with
// different implementations of indexes.
//
// See the file id_query_naive.c for a usage example.

#ifndef TEST_IMP_H
#define TEST_IMP_H

#include "record.h"

// A pointer to a function that produces an index, when called with an
// array of records and the size of the array.
typedef void* (*mk_index_fn)(const struct record*, int);

// Freeing an array produced by a mk_index_fn.
typedef void (*free_index_fn)(void*);

// Look up an ID in an index produced by mk_index_fn.
typedef const struct record* (*lookup_fn)(void*, int64_t);

// Run a query loop, using the provided functions for managing the
// index.
int id_query_loop(int argc, char** argv, mk_index_fn, free_index_fn, lookup_fn);

#endif
