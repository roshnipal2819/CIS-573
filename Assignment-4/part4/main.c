#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int ForkExec(char *temp[]) {
    pid_t pid = fork();  // Create a new process

    if (pid < 0) {  // Check for fork failure
        perror("fork failed");
        return -1;  // Return -1 on failure
    } else if (pid == 0) {  // Child process
        // Execute the command using execvp
        execvp(temp[0], temp);
        // If execvp fails
        perror("execvp failed");
        exit(EXIT_FAILURE);  // Exit child process if exec fails
    } else {  // Parent process
        int status;
        waitpid(pid, &status, 0);  // Wait for the child to finish
        return pid;  // Return the child's PID
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ForkExec [cmd] ... (at least 1 command)\n");
        return -1;  // Exit if no command is provided
    }

    int workProcessID = ForkExec(argv + 1);  // Call ForkExec with command arguments
    printf("Child process (PID=%d), performed the task!\n", workProcessID);
    return 0;  // Exit successfully
}
