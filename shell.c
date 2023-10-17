#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv)
{
    /* Declare all variables at the beginning */
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t child_pid;
    int status;
    int is_interactive;

    /* Suppress unused warning */
    (void)argc;  /* suppress unused warning */

    /* Check if it's interactive mode */
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

        child_pid = fork();

        if (child_pid == 0)  /* Child process */
        {
            char *exec_args[2];
            exec_args[0] = line;
            exec_args[1] = NULL;

            if (execve(line, exec_args, NULL) == -1)
            {
                fprintf(stderr, "%s: 1: %s: not found\n", argv[0], line);
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
