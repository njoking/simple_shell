#include "shell.h"

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int is_interactive;

    (void)argc;  /* suppress unused warning */

    is_interactive = isatty(STDIN_FILENO);

    while (1)
    {
        if (is_interactive)
            printf("($) ");

        read = getline(&line, &len, stdin);

        if (read == -1)  /* Handling EOF (Ctrl+D) */
        {
            if (is_interactive)
                printf("\n");
            break;
        }

        /* Remove the trailing newline character */
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        execute_command(line, argv[0]);
    }

    free(line);
    return 0;
}

void execute_command(char *line, char *argv0)
{
    char *exec_args[MAX_ARGS];
    char *token;
    pid_t child_pid;
    int i = 0;

    /* Check for the exit command */
    if (strcmp(line, "exit") == 0)
        exit(0);

    /* Split the line into arguments */
    token = strtok(line, " ");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        exec_args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    exec_args[i] = NULL;

    child_pid = fork();

    if (child_pid == 0)  /* Child process */
    {
        if (execve(exec_args[0], exec_args, NULL) == -1)
        {
            fprintf(stderr, "%s: 1: %s: not found\n", argv0, exec_args[0]);
            exit(127);
        }
    }
    else if (child_pid < 0)
    {
        perror("Error forking");
    }
    else  /* Parent process */
    {
        wait(NULL);
    }
}

