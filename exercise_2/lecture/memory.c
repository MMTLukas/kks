/* compile: gcc -Wall -g memory.c */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int data = 0;

int main() {
    int count = 0;
    data = getpid();
    while (1) {
        printf("data %p %d\n", &data, data);
        printf("main %p\n", main);
        printf("count %p %d\n", &count, count);
        sleep(1);
        count++;
    }
    
    return EXIT_SUCCESS;
}
