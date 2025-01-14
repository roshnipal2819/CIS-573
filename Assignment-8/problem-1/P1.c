#include <stdio.h>
#include <pthread.h>

#define COUNT 100000
int someValue = 0;

void* increment_value(void* arg) {
    for(int index = 0; index < COUNT; index++)
    {
        someValue++;                 // Critical section
    }
    return NULL;
}
void* decrement_value(void* arg) {
    for(int index = 0; index < COUNT; index++)
    {
        someValue--;                 // Critical section
    }
    return NULL;
}

int main() {
    pthread_t threads[2];

    // Create threads
    pthread_create(&threads[0], NULL, increment_value, NULL);
    pthread_create(&threads[1], NULL, decrement_value, NULL);

    // Wait for threads to finish
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    printf("Final value: %d\n", someValue);

    return 0;
}
