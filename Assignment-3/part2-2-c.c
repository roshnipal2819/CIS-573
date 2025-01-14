#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    // Open a file for writing. This file is shared between the parent and child process.
    int fd = open("outputfile.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("Failed to open file");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        dprintf(fd, "[c] This is the child process (PID: %d)\n", getpid());
    } else if (pid > 0) {
        // Parent process
        wait(NULL);  // Wait for the child process to finish
        dprintf(fd, "[p] This is the parent process (PID: %d)\n", getpid());
    } else {
        perror("Fork failed");
        close(fd);
        return 1;
    }

    close(fd);  // Close the file after writing
    return 0;
}
