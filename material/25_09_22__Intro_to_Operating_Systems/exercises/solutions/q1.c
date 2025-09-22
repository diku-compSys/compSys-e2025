#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// It forks then parent sets x to 20, and sleeps.
// 

int main() {
    int x = 10;
    if (fork() != 0) {
        x = 20;
        // sleep(1);
        printf("%d", x);
    } 
    printf("%d", x);
}