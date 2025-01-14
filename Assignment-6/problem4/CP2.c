#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include "buffer.h"  // Include the buffer structure

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <destination file>\n", argv[0]);
        return 1;
    }

    // Access shared memory
    key_t key = 5678;
    int shmid = shmget(key, sizeof(bufferStruct), 0666);
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

    // Open the destination file for writing
    FILE *dest = fopen(argv[1], "w");
    if (!dest) {
        perror("Failed to open destination file");
        return 1;
    }

    // Read data from shared memory and write to the destination file
    while (1) {
        if (buffer->done && buffer->bytesRead == 0) break;  // Check for EOF
        fwrite(buffer->data, 1, buffer->bytesRead, dest);
        getchar();  // Signal CP1 to write the next chunk
    }

    printf("File copy complete.\n");

    // Close the file and detach shared memory
    fclose(dest);
    shmdt(buffer);
    shmctl(shmid, IPC_RMID, NULL);  // Remove shared memory

    return 0;
}