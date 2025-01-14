#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 80  // Maximum length of command

int main() {
    char *args[MAX_LINE / 2 + 1];  // Command line arguments
    int should_run = 1;  // Flag to determine when to exit

    while (should_run) {
        printf("osh> ");  // Display the shell prompt
        fflush(stdout);

        // Read input from user
        char input[MAX_LINE];
        fgets(input, MAX_LINE, stdin);

        // Remove newline character from input
        input[strcspn(input, "\n")] = 0;

        // Exit if user inputs "exit"
        if (strcmp(input, "exit") == 0) {
            should_run = 0;
            continue;
        }

        // Parse the input into tokens
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;  // Null-terminate the arguments array

        // Check if the command should run in the background
        int background = 0;
        if (i > 0 && strcmp(args[i - 1], "&") == 0) {
            background = 1;
            args[i - 1] = NULL;  // Remove the "&" from the arguments
        }

        pid_t pid = fork();  // Fork a child process

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process executes the command
            if (execvp(args[0], args) < 0) {
                perror("Exec failed");
                exit(1);
            }
        } else {
            // Parent process
            if (!background) {
                wait(NULL);  // Wait for the child process to complete
            }
        }
    }
    return 0;
}
