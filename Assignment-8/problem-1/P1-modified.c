#include <pthread.h>
#include <stdio.h>

#define COUNT 100000  // You can modify this value

int someValue = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* increment(void* arg) {
    for (int i = 0; i < COUNT; i++) {
        pthread_mutex_lock(&mutex);
        someValue++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void* decrement(void* arg) {
    for (int i = 0; i < COUNT; i++) {
        pthread_mutex_lock(&mutex);
        someValue--;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, decrement, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Final value of someValue: %d\n", someValue);

    pthread_mutex_destroy(&mutex);

    return 0;
}
