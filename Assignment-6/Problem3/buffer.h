#ifndef BUFFER_H
#define BUFFER_H

#define MAX_SIZE 8  // Define buffer size

typedef struct bufferStruct {
    int in;              // Producer's pointer
    int out;             // Consumer's pointer
    int content[MAX_SIZE];  // Shared buffer for items
} bufferStruct;

#endif
