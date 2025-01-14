#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    if (argc > 1) {
        // Print all command-line arguments
        for (int i = 0; i < argc; i++) {
            printf("Argument %d: %s\n", i, argv[i]);
        }
    } else {
        // Print all environment variables
        for (int i = 0; envp[i] != NULL; i++) {
            printf("Environment Variable %d: %s\n", i, envp[i]);
        }
    }
    return 0;
}

