#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    char outBuffer[128];
    char input;
    int saved_stdout;
    int index = 1;  // Start index from 1

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <output_file>\n", argv[0]);
        exit(1);
    }

    // Save the original stdout
    saved_stdout = dup(STDOUT_FILENO);

    while (1) {
        printf("Enter 'f' (file), 's' (screen), or '0' (exit): ");
        scanf(" %c", &input);

        if (input == '0') {
            break;  // Exit the loop
        } else if (input == 'f') {
            // Open the output file specified by the user
            int file_fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (file_fd < 0) {
                perror("File open failed");
                continue;
            }

            // Redirect stdout to the file
            dup2(file_fd, STDOUT_FILENO);
            close(file_fd);
        } else if (input == 's') {
            // Restore original stdout
            dup2(saved_stdout, STDOUT_FILENO);
        }

        // Prepare the message with the current index
        snprintf(outBuffer, sizeof(outBuffer), "Index is %d\n", index++);
        
        // Print the message
        write(STDOUT_FILENO, outBuffer, strlen(outBuffer));
    }

    // Restore original stdout before exiting
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);

    return 0;
}
