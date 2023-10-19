/**
 * simple_shell - A simple shell program
 * 
 * This is a simple shell program that mimics some of the functionalities
 * of a Unix shell.
 */

/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Constants */
#define MAX_BUFFER_SIZE 1024

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
	int i = 0, command_executed = 0;

	/* Tokenize the command */
	token = strtok(command, " \t\n");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	/* Handle the 'env' command */
	if (strcmp(args[0], "env") == 0)
	{
		for (i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		return;
	}

	/* Execute the command */
	execute_external_command(args, &command_executed);

	/* If the command wasn't executed, print an error */
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
