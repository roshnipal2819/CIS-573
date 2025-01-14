#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define BUFFER_SIZE 128

int main() {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while (1) {
        // Prompt the user (optional, just to show interaction)
        const char *prompt = "Enter text: ";
        write(STDOUT_FILENO, prompt, strlen(prompt));

        // Read input from the keyboard (stdin)
        bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (bytesRead < 0) {
            perror("Error reading input");
            exit(EXIT_FAILURE);
        }

        buffer[bytesRead - 1] = '\0'; // Replace newline with null terminator

        // Dynamically allocate memory using mmap
        char *reversed = mmap(NULL, bytesRead, PROT_READ | PROT_WRITE,
                              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (reversed == MAP_FAILED) {
            perror("Error with mmap");
            exit(EXIT_FAILURE);
        }

        // Reverse the input
        for (ssize_t i = 0; i < bytesRead - 1; i++) {
            reversed[i] = buffer[bytesRead - i - 2]; // Reverse order
        }
        reversed[bytesRead - 1] = '\n'; // Add a newline for the output

        // Write the reversed input to stdout
        if (write(STDOUT_FILENO, reversed, bytesRead) < 0) {
            perror("Error writing output");
            munmap(reversed, bytesRead);
            exit(EXIT_FAILURE);
        }

        // Free the allocated memory
        if (munmap(reversed, bytesRead) < 0) {
            perror("Error unmapping memory");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
