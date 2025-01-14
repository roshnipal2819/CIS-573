#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

void printEnvpToFile(char **envp, int fd) {
    int index = 0;
    while (envp[index] != NULL) {
        dprintf(fd, "%s\n", envp[index]);
        index++;
    }
}

int main(int argc, char *argv[], char *envp[]) {
    // Open or create a temporary file for writing
    int fd = open("tempfile_envp.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    if (fd < 0) {
        perror("Failed to open temp file");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        dprintf(fd, "[c] Child Process (PID: %d), Parent (PPID: %d)\n", getpid(), getppid());
        dprintf(fd, "[c] Child envp:\n");
        printEnvpToFile(envp, fd);  // Child prints its copy of envp
    } else if (pid > 0) {
        // Parent process
        wait(NULL);  // Ensure the parent waits for the child
        dprintf(fd, "[p] Parent Process (PID: %d)\n", getpid());
        dprintf(fd, "[p] Parent envp:\n");
        printEnvpToFile(envp, fd);  // Parent prints its copy of envp
    } else {
        perror("Fork failed");
        close(fd);
        return 1;
    }

    close(fd);  // Close the file after writing
    return 0;
}
