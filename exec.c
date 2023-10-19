#include "shell.h"

/**
 * execute_command - Executes a shell command.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
    char *argv[2];
    pid_t pid;
    int status;

    argv[0] = command;
    argv[1] = NULL;

    /* Fork a new process */
    pid = fork();
    if (pid == 0)
    {
        /* This block will be executed by the child process */
        if (execve(command, argv, NULL) == -1)
        {
            perror("Error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0)
    {
        /* Forking failed */
        perror("Error");
    }
    else
    {
        /* This block will be executed by the parent process */
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}
