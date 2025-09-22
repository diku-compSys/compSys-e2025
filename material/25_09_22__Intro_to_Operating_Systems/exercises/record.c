#include "record.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// Read a single record from an open file.  This is pretty tedious, as
// we handle each field explicitly.
int read_record(struct record *r, FILE *f) {
  char *line = NULL;
  size_t n;
  if (getline(&line, &n, f) == -1) {
    free(line);
    return -1;
  }

  r->line = line;
  // printf("START: %s\n", line);
  char* start = line;
  char* end;

  // Note this methodology for reading sub strings. As each item in a line
  // is seperated by a tab we read from our starting index to the tab and 
  // assign that to a attribute, in this case the 'name'. We then update the 
  // start variable to be the next element in the line.
  if ((end = strstr(start, "\t"))) {
    *end = 0;
    r->name = start;  
    start = end+1;
  }

  if ((end = strstr(start, "\t"))) { 
    r->lon = atof(start);  *end = 0; start = end+1;
  }

  if ((end = strstr(start, "\t"))) { 
    r->lat = atof(start);  *end = 0; start = end+1;
  }

  // Discards all but last item
  // Davids solution.
  for (int i = 0; i<6; i++) { 
    if ((end = strstr(start, "\t"))) {
      start = end+1;
    } 
  }

  if ((end = strstr(start, "\n"))) { 
    r->north = atof(start); *end = 0; start = end+1;
  }
  return 0;
}

struct record* read_records(const char *filename, int *n) {
  FILE *f = fopen(filename, "r");
  *n = 0;

  if (f == NULL) {
    return NULL;
  }

  // Sanitize header
  char *line = NULL;
  size_t _n;
  getline(&line, &_n, f);
  free(line);

  int capacity = 100;
  int i = 0;
  struct record *rs = malloc(capacity * sizeof(struct record));
  while (read_record(&rs[i], f) == 0) {
    i++;
    if (i == capacity) {
      capacity *= 2;
      rs = realloc(rs, capacity * sizeof(struct record));
    }
  }

  *n = i;
  fclose(f);
  return rs;
}

void free_records(struct record *rs, int n) {
  for (int i = 0; i < n; i++) {
    free(rs[i].line);
  }
  free(rs);
}
