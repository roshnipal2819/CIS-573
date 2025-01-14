#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>

#define COUNT 1000
#define PERM 0644

int main(int argc, char *argv[])
{
	int index = 0;
	time_t now;
	int value;
	pid_t C1, C2;
	char outBuffer[128];

	// Seed the random number with different values at different times
	srand((unsigned)time(&now));
	value = rand() % 100;

	// Print parent process information
	snprintf(outBuffer, sizeof(outBuffer), "Parent process: my value is %d and my index is %d\n", value, index);
	printf("%s\n", outBuffer);
	fflush(stdout);

	// Fork the first child process C1
	C1 = fork();
	if (C1 < 0)
	{
		printf("Error: fork 1 failed\n");
		return -2;
	}

	if (C1 == 0)
	{
		// Child 1 executes this block
		for (index = 1; index <= COUNT; index++)
		{
			snprintf(outBuffer, sizeof(outBuffer), "Child 1: my value is %d and my index is %d \r\n", value, index);
			printf("%s", outBuffer);
			fflush(stdout);
			value++;
		}
		exit(0); // Child 1 terminates after its work is done
	}
	else
	{
		// Parent waits for Child 1 (C1) to complete
		waitpid(C1, NULL, 0);

		// Fork the second child process C2 after C1 has finished
		C2 = fork();
		if (C2 < 0)
		{
			printf("Error: fork 2 failed\n");
			return -2;
		}

		if (C2 == 0)
		{
			// Child 2 executes this block
			for (index = 1; index <= COUNT; index++)
			{
				snprintf(outBuffer, sizeof(outBuffer), "\tChild 2: my value is %d and my index is %d \r\n", value, index);
				printf("%s", outBuffer);
				fflush(stdout);
				value++;
			}
			exit(0); // Child 2 terminates after its work is done
		}
		else
		{
			// Parent waits for Child 2 (C2) to complete
			waitpid(C2, NULL, 0);
		}
	}

	// Parent process terminates
	printf("process %d terminated\n", getpid());
	return 0;
}
