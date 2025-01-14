#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Include time.h to use time()

#define MAX_SIZE 8  // Define buffer size

// Structure representing the bounded buffer and its pointers
typedef struct bufferStruct {
    int in;              // Producer's pointer
    int out;             // Consumer's pointer
    int content[MAX_SIZE];  // Buffer to store items
} bufferStruct;

// Function to display the current buffer content
void displayBuffer(bufferStruct *buffer) {
    printf("Buffer: ");
    int i = buffer->out;
    while (i != buffer->in) {
        printf("%d ", buffer->content[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("\n");
}

// Function to produce an item
void produce(bufferStruct *buffer) {
    if ((buffer->in + 1) % MAX_SIZE == buffer->out) {  // Check if buffer is full
        printf("<Buffer full>\n");
    } else {
        int item = rand() % 100;  // Generate a random item (0-99)
        buffer->content[buffer->in] = item;  // Add item to the buffer
        buffer->in = (buffer->in + 1) % MAX_SIZE;  // Update the 'in' pointer
        printf("Produced: %d\n", item);
    }
    displayBuffer(buffer);  // Display the buffer content
}

// Function to consume an item
void consume(bufferStruct *buffer) {
    if (buffer->in == buffer->out) {  // Check if buffer is empty
        printf("<Buffer is empty>\n");
    } else {
        int item = buffer->content[buffer->out];  // Retrieve item from the buffer
        buffer->out = (buffer->out + 1) % MAX_SIZE;  // Update the 'out' pointer
        printf("%d consumed\n", item);
    }
    displayBuffer(buffer);  // Display the buffer content
}

// Main function to manage user input and call produce/consume functions
int main() {
    srand(time(0));  // Seed the random number generator with the current time

    bufferStruct buffer = {0, 0, {0}};  // Initialize the buffer and pointers
    char command;  // Variable to store user input

    // Loop to continuously take user input and execute commands
    while (1) {
        scanf(" %c", &command);  // Read user command (with space to ignore newlines)

        if (command == 'p') {  // Produce an item
            produce(&buffer);
        } else if (command == 'c') {  // Consume an item
            consume(&buffer);
        } else if (command == '0') {  // Exit the program
            printf("Exiting...\n");
            break;
        } else {  // Handle invalid input
            printf("Invalid command. Try again.\n");
        }
    }

    return 0;  // Program exits successfully
}
