#include "shell.h"

/**
 * execute_external_command - Executes an external shell command.
 * @args: The arguments array.
 * @command_executed: Pointer to flag indicating if command was executed.
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

	execute_command_from_path(args, command_executed, path_token);
	free(path_copy);
}

/**
 * execute_command_from_path - Executes command from PATH tokens.
 * @args: The arguments array.
 * @command_executed: Pointer to flag indicating if command was executed.
 * @path_token: The tokenized PATH string.
 */
void execute_command_from_path(char *args[], int *command_executed,
							   char *path_token)
{
	char command_path[MAX_BUFFER_SIZE];

	while (path_token != NULL)
	{
		snprintf(command_path, sizeof(command_path), "%s/%s",
				 path_token, args[0]);
		if (access(command_path, X_OK) == 0)
		{
			execute_fork(args, command_executed, command_path);
			break;
		}
		path_token = strtok(NULL, ":");
	}
}

/**
 * execute_fork - Forks and executes a command.
 * @args: The arguments array.
 * @command_executed: Pointer to flag indicating if command was executed.
 * @command_path: The full path to the command to execute.
 */
void execute_fork(char *args[], int *command_executed, char *command_path)
{
	pid_t pid;

	pid = fork();
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
	}
}

/**
 * execute_command - Executes a shell command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	char *args[MAX_BUFFER_SIZE];
	char *token;
	int i = 0, command_executed = 0;

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
		{
			printf("%s\n", environ[i]);
		}
		return;
	}

	execute_external_command(args, &command_executed);

	if (!command_executed)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
	}
}

/**
 * main - The main function for the simple shell.
 * Return: 0 on success, otherwise returns the error code.
 */
int main(void)
{
	char buffer[MAX_BUFFER_SIZE];
	size_t length;

	while (1)
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
		{
			break;
		}

		length = strlen(buffer);
		if (buffer[length - 1] == '\n')
		{
			buffer[length - 1] = '\0';
		}

		if (strcmp(buffer, "exit") == 0)
		{
			break;
		}

		execute_command(buffer);
	}

	printf("Exiting shell...\n");
	return (0);
}
