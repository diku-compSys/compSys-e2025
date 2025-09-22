#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    int fd = open("file.txt", O_WRONLY);
    if (fd == -1) {
        printf("%s\n", fd);
    }
    if (fork() == 0) {
        // Child
        if (write(fd, "child\n", sizeof("child")) == -1) {
            printf("Child cant write!\n");
        } 
    }
    if (write(fd, "parent\n", sizeof("parent")) == -1) {
        printf("Parent cant write!\n");
    }
    close(fd);
}