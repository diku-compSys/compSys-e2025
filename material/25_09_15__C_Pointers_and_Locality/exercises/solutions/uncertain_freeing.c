#include <stdlib.h>
#include <stdio.h>

int n = 10;
int* a = NULL;
int* b = NULL;
int* c = NULL;
long int checksum = 0;

void count(int* arr) {
    for (int i=0; i<n; i++) {
        checksum += arr[i];
    }
}

void func1(){
    int used_a = 0;
    int used_b = 0;
    int used_c = 0;
    if (checksum == 0) {
        count(a);
        used_a = 1;
    } else {
        if (checksum % 10 == 0) {
            count(c);
            used_c = 1;
        }
        else {
            count(b);
            used_b = 1;
            if (1000000 - checksum < 0) {
                count(c);
                used_c = 1;
            }
        }
    }
    printf("Func1: %d %d %d\n", used_a, used_b, used_c);
}

void func2(){
    int used_a = 0;
    int used_b = 0;
    int used_c = 0;
    if (checksum == 0) {
        count(b);
        used_b = 1;
    } else {
        if (checksum % 5 == 0) {
            count(b);
            used_b = 1;
        }
        if (checksum < (254*254)) {
            count(a);
            used_a = 1;
        }
    }
    printf("Func2: %d %d %d\n", used_a, used_b, used_c);
}

void func3(){
    int used_a = 0;
    int used_b = 0;
    int used_c = 0;
    if (checksum != 0) {
        count(c);
        used_c = 1;
        if (checksum > 100) {
            if (checksum % 10) {
                count(a);
                used_a = 1;
            } else {
                if (checksum + checksum > 10000) {
                    count(b);
                    used_b = 1;
                }
            }
        }
    } else {
        if (checksum % 5 == 0) {
            count(b);
            used_b = 1;
        } else {
            count(a);
            used_a = 1;
        }
    
    }
    printf("Func3: %d %d %d\n", used_a, used_b, used_c);
}

int main(void) {
    a = malloc(n * sizeof(int));
    for (int i=0; i<n; i++) {
        a[i] = i;
    }
    b = malloc(n * sizeof(int));
    for (int i=0; i<n; i++) {
        b[i] = i*10;
    }
    c = malloc(n * sizeof(int));
    for (int i=0; i<n; i++) {
        c[i] = i*100;
    }

    // You can only add free statements below here and should do so are early as
    // possible without altering the result
    func1();
    func3();
    func2();
    func3();
    func2();
    func3();
    func3();
    func2();
    func2();
    func3();
    func2();
    func3();
    func1();
    func2();
    func3();
    func2();
    func3();
    func1();
    func1();
    func3();
    func1();
    free(c);
    func2();
    free(a);
    func1();
    func2();
    free(b);

    if (checksum != 65025)
        printf("You've altered functionality\n");
    printf("%ld\n", checksum);

    return 0;
}