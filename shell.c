#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Entry point for the simple shell
 *
 * Return: 0 on success, EXIT_FAILURE on error
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	pid_t pid;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		nread = getline(&line, &len, stdin);

		if (nread == -1 && feof(stdin))
		{
			exit(EXIT_SUCCESS);
		}

		line[nread - 1] = '\0';

		pid = fork();
		
		if (pid == 0)
		{
			char *argv[] = {line, NULL};
			execve(line, argv, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("fork");
		}
	}
	free(line);

	return (0);
}
