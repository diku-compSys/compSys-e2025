#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct array_elem {
    int a;
    int b;
};

void print_arr(char* s, int* arr, int n) {
    printf("%s: ", s);
    for (int i=0; i<n-1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[n-1]);
}

void print_arr_elems(char* s, struct array_elem* arr, int n) {
    printf("%s: ", s);
    for (int i=0; i<n-1; i++) {
        printf("(a: %d, b: %d), ", arr[i].a, arr[i].b);
    }
    printf("(a: %d, b: %d)\n", arr[n-1].a, arr[n-1].b);
}

int int_ascending(const void *px, const void *py) {
  int x = *(int*)px;
  int y = *(int*)py;

  if (x < y) {
    return -1;
  } else if (x == y) {
    return 0;
  } else {
    return 1;
  }
}

int int_descending(const void *px, const void *py) {
  int x = *(int*)px;
  int y = *(int*)py;

  if (x > y) {
    return -1;
  } else if (x == y) {
    return 0;
  } else {
    return 1;
  }
}

int array_elems_a(const void *px, const void *py) {
  int x = ((struct array_elem*)px)->a;
  int y = ((struct array_elem*)py)->a;

  if (x < y) {
    return -1;
  } else if (x == y) {
    return 0;
  } else {
    return 1;
  }
}

int array_elems_b(const void *px, const void *py) {
  int x = ((struct array_elem*)px)->b;
  int y = ((struct array_elem*)py)->b;

  if (x < y) {
    return -1;
  } else if (x == y) {
    return 0;
  } else {
    return 1;
  }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s N\n", argv[0]);
        exit(1);
    }
    int n = atoi(argv[1]);

    int* arr = malloc(n*sizeof(int));

    // If you want to generate the same numbers every time comment out the 
    // below line
    srand(time(NULL));

    for (int i=0; i<n; i++) {
        arr[i] = rand() % 100 + 1;
    }

    print_arr("Initial array\t\t\0", arr, n);

    // Most of your work should be done below here

    qsort(arr, n, sizeof(int), int_ascending);

    print_arr("Ascending\t\t\0", arr, n);

    qsort(arr, n, sizeof(int), int_descending);

    print_arr("Descending\t\t\0", arr, n);

    free(arr);

    struct array_elem* arr_elems = malloc(n*sizeof(struct array_elem*));
    for (int i=0; i<n; i++) {
        struct array_elem arr_elem;
        arr_elem.a = rand() % 100 + 1;
        arr_elem.b = rand() % 100 + 1;
        arr_elems[i] = arr_elem;
    }

    print_arr_elems("Initial array_elems\t\0", arr_elems, n);

    qsort(arr_elems, n, sizeof(struct array_elem*), array_elems_a);

    print_arr_elems("array_elems a\t\t\0", arr_elems, n);

    qsort(arr_elems, n, sizeof(struct array_elem*), array_elems_b);

    print_arr_elems("array_elems b\t\t\0", arr_elems, n);

    free(arr_elems);

}