#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

void copyFile(int source, int destination) {
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    while ((bytesRead = read(source, buffer, BUFFER_SIZE)) > 0) {
        if (write(destination, buffer, bytesRead) != bytesRead) {
            perror("Error writing to file");
            exit(EXIT_FAILURE);
        }
    }

    if (bytesRead < 0) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc != 5) {
        fprintf(stderr, "Error! Usage: myCAT <s,e> file1 file2 file3\n");
        return EXIT_FAILURE;
    }

    // Validate the flag
    char *flag = argv[1];
    if (strcmp(flag, "-s") != 0 && strcmp(flag, "-e") != 0) {
        fprintf(stderr, "Error! Usage: you should use either '-s' or '-e' then the file names\n");
        return EXIT_FAILURE;
    }

    // Open the files
    int file1 = open(argv[2], O_RDONLY);
    int file2 = open(argv[3], O_RDONLY);
    int file3 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Check if files opened successfully
    if (file1 < 0) {
        perror("Error opening file1");
        return EXIT_FAILURE;
    }
    if (file2 < 0) {
        perror("Error opening file2");
        close(file1);
        return EXIT_FAILURE;
    }
    if (file3 < 0) {
        perror("Error opening file3");
        close(file1);
        close(file2);
        return EXIT_FAILURE;
    }

    // Perform the file concatenation based on the flag
    if (strcmp(flag, "-s") == 0) {
        copyFile(file1, file3);
        copyFile(file2, file3);
    } else if (strcmp(flag, "-e") == 0) {
        copyFile(file2, file3);
        copyFile(file1, file3);
    }

    // Close the files
    close(file1);
    close(file2);
    close(file3);

    printf("Files concatenated successfully.\n");
    return EXIT_SUCCESS;
}