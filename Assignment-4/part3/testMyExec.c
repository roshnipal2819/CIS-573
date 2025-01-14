#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) { envp[1] = "USER=FirstName_LastName"; printf("testMyExec environment variables:\n"); for (int i = 0; envp[i] != NULL; i++) {
printf("envp[%d] = %s\n", i, envp[i]); }
execle("./myExec", "myExec", NULL, envp); perror("execle failed");
return 1;
}