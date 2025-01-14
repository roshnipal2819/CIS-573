#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_LENGTH 10  // Size of the buffer

int buffer[MAX_LENGTH];  // Shared buffer
int count = 0;           // Number of items in the buffer
int in = 0;              // Producer index
int out = 0;             // Consumer index

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void* producer(void* arg) {
    int num_items = *((int*)arg);
    for (int i = 0; i < num_items; i++) {
        pthread_mutex_lock(&mutex);
        
        // Wait if the buffer is full
        while (count == MAX_LENGTH) {
            pthread_cond_wait(&not_full, &mutex);
        }

        // Produce an item and add it to the buffer
        buffer[in] = i;
        in = (in + 1) % MAX_LENGTH;
        count++;
        printf("Produced item %d, Items in buffer: %d\n", i, count);

        // Signal that the buffer is not empty
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
        
        usleep(100000);  // Simulate time taken to produce an item (100 ms)
    }
    return NULL;
}

void* consumer(void* arg) {
    int num_items = *((int*)arg);
    for (int i = 0; i < num_items; i++) {
        pthread_mutex_lock(&mutex);

        // Wait if the buffer is empty
        while (count == 0) {
            pthread_cond_wait(&not_empty, &mutex);
        }

        // Consume an item from the buffer
        int item = buffer[out];
        out = (out + 1) % MAX_LENGTH;
        count--;
        printf("Consumed item %d, Items in buffer: %d\n", item, count);

        // Signal that the buffer is not full
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        
        usleep(150000);  // Simulate time taken to consume an item (150 ms)
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    int num_items;

    // Get the number of items to produce from the user
    printf("Enter the number of items to produce: ");
    if (scanf("%d", &num_items) != 1 || num_items <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    // Create producer and consumer threads
    if (pthread_create(&producer_thread, NULL, producer, &num_items) != 0) {
        fprintf(stderr, "Error creating producer thread.\n");
        return 1;
    }

    if (pthread_create(&consumer_thread, NULL, consumer, &num_items) != 0) {
        fprintf(stderr, "Error creating consumer thread.\n");
        return 1;
    }

    // Wait for both threads to finish
    if (pthread_join(producer_thread, NULL) != 0) {
        fprintf(stderr, "Error joining producer thread.\n");
        return 1;
    }

    if (pthread_join(consumer_thread, NULL) != 0) {
        fprintf(stderr, "Error joining consumer thread.\n");
        return 1;
    }

    // Destroy mutex and condition variables
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}
