#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 100

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t child_pid;
    int status;
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

        /* Check for the exit command */
        if (strcmp(line, "exit") == 0)
        {
            free(line);
            return 0;
        }

        /* Split the line into arguments */
        char *exec_args[MAX_ARGS];
        char *token = strtok(line, " ");
        int i = 0;
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
                fprintf(stderr, "%s: 1: %s: not found\n", argv[0], exec_args[0]);
                exit(127);
            }
        }
        else if (child_pid < 0)
        {
            perror("Error forking");
        }
        else  /* Parent process */
        {
            wait(&status);
        }
    }

    free(line);

    return 0;
}
