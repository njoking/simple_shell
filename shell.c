#include "shell.h"

/**
 * execute_fork - Executes fork and handles child and parent processes.
 * @command_path: The complete path to the executable.
 * @args: The arguments array.
 * @command_executed: Pointer to flag indicating if a command was executed.
 */
void execute_fork(char *command_path, char *args[], int *command_executed)
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
	}
}

/**
 * execute_external_command - Executes an external shell command.
 * @args: The arguments array.
 * @command_executed: Pointer to flag indicating if a command was executed.
 */
void execute_external_command(char *args[], int *command_executed)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *path_token = strtok(path_copy, ":");

	while (path_token != NULL)
	{
		char command_path[MAX_BUFFER_SIZE];
		snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);

		if (access(command_path, X_OK) == 0)
			execute_fork(command_path, args, command_executed);

		if (*command_executed)
			break;

		path_token = strtok(NULL, ":");
	}
	free(path_copy);
}

/* ... rest of the code remains the same ... */
