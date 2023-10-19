#include "shell.h"

/**
 * main - Entry point for the shell.
 * Return: 0 if successful
 */
int main(void)
{
    char *line;
    char *command;
    int interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (interactive)
        {
            write(STDOUT_FILENO, "($) ", 4);
        }

        line = read_command();
        if (feof(stdin))
        {
            if (interactive)
            {
                write(STDOUT_FILENO, "\n", 1);
            }
            exit(EXIT_SUCCESS);
        }

        command = strtok(line, "\n\t\r ");
        if (command)
        {
            execute_command(command);
        }
        free(line);
    }
    return (0);
}
