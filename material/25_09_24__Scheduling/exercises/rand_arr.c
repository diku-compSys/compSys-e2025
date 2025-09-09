#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_arr(char* s, int* arr, int n) {
    printf("%s: ", s);
    for (int i=0; i<n-1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d\n", arr[n-1]);
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

    print_arr("Initial array\0", arr, n);

    // Most of your work should be done below here

    free(arr);
}