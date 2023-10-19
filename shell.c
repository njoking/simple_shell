#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

/**
 * main - Entry point for the simple shell
 * Return: 0 on success, EXIT_FAILURE on error
 */
int main(void)
{
	char line[1024];
	ssize_t nread;
	pid_t pid;
	char *argv[] = {NULL, NULL};

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		nread = read(STDIN_FILENO, line, sizeof(line) - 1);

		if (nread == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}

		if (nread > 0 && line[nread - 1] == '\n')
		{
			line[nread - 1] = '\0';
		}

		pid = fork();
		if (pid == 0)
		{
			argv[0] = line;
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
	return (0);
}
