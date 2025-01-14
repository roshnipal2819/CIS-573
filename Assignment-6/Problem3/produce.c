#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include "buffer.h"  // Include shared buffer structure

// Function to print the entire buffer
void printBuffer(bufferStruct *buffer) {
    printf("Buffer: ");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", buffer->content[i]);  // Print each item in the buffer
    }
    printf("\n");
}

int main() {
    key_t key = 1234;  // Shared memory key
    int shmid = shmget(key, sizeof(bufferStruct), 0666 | IPC_CREAT);  // Create shared memory
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    bufferStruct *buffer = (bufferStruct *)shmat(shmid, NULL, 0);  // Attach shared memory
    if (buffer == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    buffer->in = buffer->out = 0;  // Initialize pointers
    srand(time(0));  // Seed the random number generator

    printf("Press Enter to produce an item or '0' to exit:\n");
    char command;
    while (1) {
        command = getchar();
        if (command == '0') break;

        if ((buffer->in + 1) % MAX_SIZE == buffer->out) {
            printf("Buffer is full ...\n");
        } else {
            int item = rand() % 100;  // Generate a random item (0-99)
            buffer->content[buffer->in] = item;
            buffer->in = (buffer->in + 1) % MAX_SIZE;
            printf("Produced: %d\n", item);
        }
        printBuffer(buffer);  // Print the entire buffer after production
    }

    shmdt(buffer);  // Detach shared memory
    return 0;
}
