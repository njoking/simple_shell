#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - The main function for the simple shell
 * Return: 0 on success
 */
int main(void)
{
	char buffer[1024];
	char *args[2];
	pid_t pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		size_t length = strlen(buffer);

		if (buffer[length - 1] == '\n')
			buffer[length - 1] = '\0';

		if (strlen(buffer) == 0)
			continue;

		args[0] = buffer;
		args[1] = NULL;

		pid = fork();
		if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("./shell");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
