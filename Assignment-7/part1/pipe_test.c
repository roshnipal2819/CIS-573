#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MSG_SIZE 50

int main() {
    int pipeFD[2];  // File descriptors for the pipe
    pid_t pid;      // Process ID
    char buffer[MSG_SIZE];
    int bytesRead;

    // Create a pipe and check for errors
    if (pipe(pipeFD) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid = fork();  // Fork a new process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {  // Parent process (Writer)
        close(pipeFD[0]);  // Close unused read end

        char *messages[3] = {"Hello CIS573", "Message 2", "Message 3"};
        for (int i = 0; i < 3; i++) {
            write(pipeFD[1], messages[i], strlen(messages[i]) + 1);  // Write message
            printf("Parent sent: %s\n", messages[i]);
        }

        close(pipeFD[1]);  // Close write end after writing
        wait(NULL);        // Wait for child process to finish
    } else {  // Child process (Reader)
        close(pipeFD[1]);  // Close unused write end

        while ((bytesRead = read(pipeFD[0], buffer, MSG_SIZE)) > 0) {
            buffer[bytesRead] = '\0';  // Null-terminate the string
            printf("Child received: %s (Bytes read: %d)\n", buffer, bytesRead);
        }

        if (bytesRead == -1) {
            perror("Read failed");
            exit(1);
        }

        close(pipeFD[0]);  // Close read end
    }

    return 0;
}
