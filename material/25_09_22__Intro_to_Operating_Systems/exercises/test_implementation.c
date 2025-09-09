#include <stdio.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "test_implementation.h"

int main(int argc, char** argv) {

  if (argc != 2) {
    fprintf(stderr, "Usage: %s FILE\n", argv[0]);
    exit(1);
  }

  int n;
  struct record *rs = read_records(argv[1], &n);

  if (rs) {
    char *line = NULL;

    fprintf(stdout, "Read %d records from %s\n", n, argv[1]);

    // Note these tests are all fairly crude and easy to code your way around
    // without actually solving the problem. You may wish to alter or expand
    // them to make sure you aren't just sidestepping them.

    if (strncmp(rs[0].name, "name", 4) == 0) {
      fprintf(stdout, "ERROR - Read data header into records!\n");
    }

    if (n != 100) {
      fprintf(stdout, "ERROR - Read incorrect amount of records! Read '%d' but expected '100'\n", n);
    }    
    
    if (strncmp(rs[n-1].name, "Uruguay", 7) != 0) {
      fprintf(stdout, "ERROR - Didn't read in all records correctly. Expected the final record to be '%s'\n", rs[n-1].name);
    }

    if (rs[0].lat != 46.7995347) {
      fprintf(stdout, "ERROR - Not reading in lattitude correctly. Read '%f' but expected '46.799535'\n", rs[0].lat);
    }
    
    if (strncmp(rs[0].name, "France", 6) != 0) {
      fprintf(stdout, "ERROR - Not reading in display_name correctly. Read '%s' but expected 'France'\n", rs[0].display_name);
    }
    
    if (rs[0].north != 51.2) {
      fprintf(stdout, "ERROR - Not reading in north correctly. Read '%f' but expected '51.2'\n", rs[0].north);
    }

    free(line);
    free_records(rs, n);
    return 0;
  } else {
    fprintf(stderr, "Failed to read input from %s (errno: %s)\n",
            argv[1], strerror(errno));
    return 1;
  }
}