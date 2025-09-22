#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// It forks then parent sets x to 20, and sleeps.
// 

int main() {
    int x;
    if (fork() == 0) {
        printf("Child sleeping...\n");
        sleep(2);
    } else {
        wait(&x);
        printf("Parent done!\n");
    }
}