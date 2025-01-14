
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[], char *envp[]) {
printf("myExec environment variables:\n"); for (int i = 0; envp[i] != NULL; i++) {
printf("envp[%d] = %s\n", i, envp[i]); }
return 0; }
