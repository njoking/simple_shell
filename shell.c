#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 1024

/**
 * execute_command - function to execute a command
 * @command: command to be executed
 */
void execute_command(char *command)
{
	char *args[MAX_BUFFER_SIZE];
	char *token;
	int i = 0;

	token = strtok(command, " \t\n");
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " \t\n");
		i++;
	}
	args[i] = NULL;

	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		char command_path[MAX_BUFFER_SIZE];

		snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);
		if (access(command_path, X_OK) == 0)
		{
			pid_t pid = fork();

			if (pid == 0)
			{
				if (execv(command_path, args) == -1)
				{
					perror("Execv failed");
					exit(EXIT_FAILURE);
				}
			}
			else if (pid > 0)
			{
				waitpid(pid, NULL, 0);
				break;
			}
			else
			{
				perror("Fork failed");
			}
		}
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
}

/**
 * main - main function for the shell
 * Return: 0 on success
 */
int main(void)
{
	char buffer[MAX_BUFFER_SIZE];

	while (1)
	{
		printf("$ ");
		fflush(stdout);
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
			break;
		size_t length = strlen(buffer);
		if (buffer[length - 1] == '\n')
			buffer[length - 1] = '\0';

		if (strcmp(buffer, "exit") == 0)
			break;
		if (strcmp(buffer, "env") == 0)
		{
			for (int i = 0; environ[i]; i++)
				printf("%s\n", environ[i]);
		}
		else
			execute_command(buffer);
	}
	printf("Exiting shell...\n");
	return (0);
}

