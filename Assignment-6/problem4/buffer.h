#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_SIZE 1024  // Size of shared memory buffer

typedef struct bufferStruct {
    char data[BUFFER_SIZE];  // Buffer to store file data
    int bytesRead;  // Number of bytes read
    int done;  // Flag to indicate end of file (EOF)
} bufferStruct;

#endif

