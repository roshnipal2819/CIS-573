#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

volatile sig_atomic_t keep_running = 1;

void handle_sigint(int sig) {
    keep_running = 0;
}

void handle_sigalrm(int sig) {
    // Get the current time
    time_t current_time;
    time(&current_time);
    struct tm* local_time = localtime(&current_time);

    // Print the current time in HH:MM:SS format
    printf("%02d:%02d:%02d\n", local_time->tm_hour, local_time->tm_min, local_time->tm_sec);

    // Schedule the next alarm
    alarm(1);
}

int main() {
    // Set up signal handler for SIGINT to stop the program gracefully
    struct sigaction sa_int;
    sa_int.sa_handler = handle_sigint;
    sa_int.sa_flags = 0;
    sigemptyset(&sa_int.sa_mask);
    if (sigaction(SIGINT, &sa_int, NULL) == -1) {
        perror("Error setting up SIGINT handler");
        exit(EXIT_FAILURE);
    }

    // Set up signal handler for SIGALRM to update the time every second
    struct sigaction sa_alrm;
    sa_alrm.sa_handler = handle_sigalrm;
    sa_alrm.sa_flags = 0;
    sigemptyset(&sa_alrm.sa_mask);
    if (sigaction(SIGALRM, &sa_alrm, NULL) == -1) {
        perror("Error setting up SIGALRM handler");
        exit(EXIT_FAILURE);
    }

    // Start the alarm to trigger every second
    alarm(1);

    // Run until SIGINT is received
    while (keep_running) {
        pause();  // Wait for signals
    }

    printf("Program terminated gracefully.\n");
    return 0;
}
