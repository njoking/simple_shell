#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * main - Entry point for the simplified shell.
 * Return: 0 on success, otherwise exit status.
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    pid_t child_pid;

    while (1)
    {
        printf("#cisfun$ ");
        fflush(stdout);  // Flush the output buffer to make sure the prompt is displayed

        read = getline(&line, &len, stdin);

        if (read == -1)  // Handling EOF (Ctrl+D)
        {
            printf("\n");
            break;
        }

        if (line[read - 1] == '\n')
            line[read - 1] = '\0';

        if (strcmp(line, "exit") == 0)  // Exit command
            break;

        child_pid = fork();
        if (child_pid == 0)  // Child process
        {
            if (execve(line, NULL, NULL) == -1)
            {
                fprintf(stderr, "%s: No such file or directory\n", line);
                exit(127);
            }
        }
        else if (child_pid < 0)  // Fork failed
        {
            perror("Error forking");
            continue;
        }
        else  // Parent process
        {
            wait(NULL);
        }
    }
    free(line);
    return (0);
}
