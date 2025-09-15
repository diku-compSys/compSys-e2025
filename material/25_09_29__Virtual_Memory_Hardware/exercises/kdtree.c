#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct point{
  int x;
  int y;
  int z;
};

int read_point(struct point *p, FILE *f) {
  char *line = NULL;
  size_t n;
  if (getline(&line, &n, f) == -1) {
    free(line);
    return -1;
  }

  char* start = line;
  char* end;

  if ((end = strstr(start, "\t"))) {
    p->x = atoi(start); 
    *end = 0; 
    start = end+1;
  }

  if ((end = strstr(start, "\t"))) {
    p->y = atoi(start); 
    *end = 0; 
    start = end+1;
  }

  if ((end = strstr(start, "\n"))) {
    p->z = atoi(start); 
    *end = 0; 
    start = end+1;
  }

  return 0;
}

struct point* read_points(const char *filename, int *n) {
  FILE *f = fopen(filename, "r");
  *n = 0;

  if (f == NULL) {
    return NULL;
  }

  int capacity = 100;
  int i = 0;
  struct point *rs = malloc(capacity * sizeof(struct point));
  while (read_point(&rs[i], f) == 0) {
    i++;
    if (i == capacity) {
      capacity *= 2;
      rs = realloc(rs, capacity * sizeof(struct point));
    }
  }

  *n = i;
  fclose(f);
  return rs;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <DATA>\n", argv[0]);
    exit(1);
  }
  int n;

  struct point* points = read_points(argv[1], &n);

  printf("Read %d points\n", n);

  free(points);
}