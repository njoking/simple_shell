/**
 * simple_shell - A simple shell program
 *
 * This is a simple shell program that mimics some of the functionalities
 * of a Unix shell.
 */

#include "shell.h"

/**
 * execute_external_command - Executes an external shell command.
 * @args: The arguments array.
 * @command_executed: Pointer to flag indicating if a command was executed.
 *
 * Return: None.
 */
void execute_external_command(char *args[], int *command_executed)
{
	char *path = getenv("PATH");
	char *path_copy, *path_token;

	if (path == NULL)
	{
		perror("Failed to get PATH");
		return;
	}

	path_copy = strdup(path);
	path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		char command_path[MAX_BUFFER_SIZE];

		snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);

		if (access(command_path, X_OK) == 0)
		{
			pid_t pid = fork();

			if (pid < 0)
			{
				perror("Fork failed");
			}
			else if (pid == 0)
			{
				if (execv(command_path, args) == -1)
				{
					perror("Execv failed");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				waitpid(pid, NULL, 0);
				*command_executed = 1;
				break;
			}
		}
		path_token = strtok(NULL, ":");
	}
	free(path_copy);
}

/**
 * execute_command - Executes a shell command.
 * @command: The command to execute.
 *
 * Return: None.
 */
void execute_command(char *command)
{
	char *args[MAX_BUFFER_SIZE];
	char *token;
	int i = 0;
	int command_executed = 0;

	token = strtok(command, " \t\n");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return;
	}

	execute_external_command(args, &command_executed);

	if (!command_executed)
		fprintf(stderr, "%s: command not found\n", args[0]);
}

/**
 * main - The main function for the simple shell.
 *
 * Return: 0 on success, otherwise returns the error code.
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

		execute_command(buffer);
	}

	printf("Exiting shell...\n");
	return (0);
}
