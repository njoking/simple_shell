#include "shell.h"

/**
 * read_command - Reads a line of input from stdin.
 * Return: A string containing the line of input.
 */
char *read_command(void)
{
    char *line = NULL;
    size_t len = 0;

    /* Display prompt */
    write(STDOUT_FILENO, "$ ", 2);

    /* Read a line */
    getline(&line, &len, stdin);

    return line;
}
