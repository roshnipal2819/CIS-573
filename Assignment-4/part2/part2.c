#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pipefd[2];  // Pipe file descriptors: pipefd[0] for reading, pipefd[1] for writing
    pid_t pid;
    int sum = 0;    // Variable to hold the sum

    // Check if the number of arguments is valid (at least 1 number)
    if (argc < 2) {
        printf("Usage: %s <number1> <number2> ... <numberN>\n", argv[0]);
        return -1;
    }

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a new process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        close(pipefd[0]);  // Close unused read end of the pipe

        // Compute the sum of the command-line arguments
        for (int i = 1; i < argc; i++) {
            sum += atoi(argv[i]);  // Convert the string argument to an integer and add to sum
        }

        // Write the sum to the pipe
        write(pipefd[1], &sum, sizeof(sum));
        close(pipefd[1]);  // Close the write end after writing

        exit(EXIT_SUCCESS);  // Exit child process
    } else {  // Parent process
        close(pipefd[1]);  // Close unused write end of the pipe

        // Wait for the child process to finish
        wait(NULL);

        // Read the sum from the pipe
        read(pipefd[0], &sum, sizeof(sum));
        close(pipefd[0]);  // Close the read end after reading

        // Print the sum
        printf("The sum is: %d\n", sum);
    }

    return 0;
}
