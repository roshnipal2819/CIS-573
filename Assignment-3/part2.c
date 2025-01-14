#include <stdio.h>
#include <unistd.h>

int main() {
    int i;  

    for (i=0; i < 1; i++) {
        if(fork())
        printf("Hello from process %d\n", getpid());
    }
    sleep(20);
    return 0;
}
