#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
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
    int shmid = shmget(key, sizeof(bufferStruct), 0666);  // Access shared memory
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    bufferStruct *buffer = (bufferStruct *)shmat(shmid, NULL, 0);  // Attach shared memory
    if (buffer == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    printf("Press Enter to consume an item or '0' to exit:\n");
    char command;
    while (1) {
        command = getchar();
        if (command == '0') break;

        if (buffer->in == buffer->out) {
            printf("Buffer is empty ...\n");
        } else {
            int item = buffer->content[buffer->out];
            buffer->out = (buffer->out + 1) % MAX_SIZE;
            printf("%d consumed\n", item);
        }
        printBuffer(buffer);  // Print the entire buffer after consumption
    }

    shmdt(buffer);  // Detach shared memory
    shmctl(shmid, IPC_RMID, NULL);  // Remove shared memory
    return 0;
}
