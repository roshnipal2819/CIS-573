#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Function to read a line from a file descriptor
int readLine(int fd, char *buffer, int size) {
    int i = 0;
    char ch;
    while (i < size - 1) {
        ssize_t bytesRead = read(fd, &ch, 1);
        if (bytesRead <= 0) break; // End of file or error
        buffer[i++] = ch;
        if (ch == '\n') break; // End of line
    }
    buffer[i] = '\0';
    return i;
}

int main(int argc, char *argv[]) {
    int numLines = 5; // Default number of lines
    char *filename;
    int fd;

    // Check for correct number of arguments
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "Usage: ./myHEAD [-n num_lines] file\n");
        return EXIT_FAILURE;
    }

    // Handle arguments
    if (argc == 2) {
        filename = argv[1];
    } else if (argc == 4 && strcmp(argv[1], "-n") == 0) {
        numLines = atoi(argv[2]);
        if (numLines <= 0) {
            fprintf(stderr, "Error: Number of lines must be greater than 0\n");
            return EXIT_FAILURE;
        }
        filename = argv[3];
    } else {
        fprintf(stderr, "Usage: ./myHEAD [-n num_lines] file\n");
        return EXIT_FAILURE;
    }

    // Open the file
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read and print the first numLines lines
    char buffer[BUFFER_SIZE];
    int lineCount = 0;

    while (lineCount < numLines) {
        int bytesRead = readLine(fd, buffer, BUFFER_SIZE);
        if (bytesRead == 0) break; // End of file
        if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
            perror("Error writing output");
            close(fd);
            return EXIT_FAILURE;
        }
        lineCount++;
    }

    close(fd);
    return EXIT_SUCCESS;
}
