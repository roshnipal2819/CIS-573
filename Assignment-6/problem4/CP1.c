#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include "buffer.h"  // Include the buffer structure

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    // Create shared memory
    key_t key = 5678;
    int shmid = shmget(key, sizeof(bufferStruct), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }

    // Attach shared memory
    bufferStruct *buffer = (bufferStruct *)shmat(shmid, NULL, 0);
    if (buffer == (void *)-1) {
        perror("shmat failed");
        return 1;
    }

    // Open the source file for reading
    FILE *src = fopen(argv[1], "r");
    if (!src) {
        perror("Failed to open source file");
        return 1;
    }

    // Read data from the source file and write to shared memory
    while ((buffer->bytesRead = fread(buffer->data, 1, BUFFER_SIZE, src)) > 0) {
        buffer->done = 0;  // Not done yet
        getchar();  // Wait for CP2 to read the data
    }

    // Signal that we are done
    buffer->done = 1;
    printf("File copy complete.\n");

    // Close the file and detach shared memory
    fclose(src);
    shmdt(buffer);

    return 0;
}