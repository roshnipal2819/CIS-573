#include <stdio.h>
#include <string.h>

#define MAX_NUM_OF_ARGS 5
#define MAX_ARG_SIZE 256

int main(int argc, char *argv[]) {
    char argumentArray[MAX_NUM_OF_ARGS][MAX_ARG_SIZE];
    
    // Initialize the array with "defaultArg"
    for (int i = 0; i < MAX_NUM_OF_ARGS; i++) {
        strcpy(argumentArray[i], "defaultArg");
    }

    // Populate the array with arguments, if provided
    for (int i = 0; i < argc && i < MAX_NUM_OF_ARGS; i++) {
        strcpy(argumentArray[i], argv[i]);
    }

    // Print the populated array
    for (int i = 0; i < MAX_NUM_OF_ARGS; i++) {
        printf("argumentArray[%d]: %s\n", i, argumentArray[i]);
    }

    // Check for too many arguments
    if (argc > MAX_NUM_OF_ARGS) {
        printf("Usage: MyCommand2 Arg1 Arg2...\n     Your argument exceeded the maximum of arguments(4)\n");
    }

    return 0;
}

