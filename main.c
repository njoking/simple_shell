#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXLINE 1024

/**
 * display_prompt - Display the shell prompt
 */
void display_prompt(void)
{
    char prompt[] = "#cisfun$ ";

    write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * handle_error - Handle command execution errors
 * @progname: Name of the running program
 * @cmd: The command that failed
 */
void handle_error(char *progname, char *cmd)
{
    write(STDERR_FILENO, progname, strlen(progname));
    write(STDERR_FILENO, ": 1: ", 5);
    write(STDERR_FILENO, cmd, strlen(cmd));
    write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * main - Entry point for the shell
 * @argc: Argument count
 * @argv: Argument vector
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
    char *line = NULL;
    size_t len = 0;
    char *argv_exec[2];
    pid_t pid;
    int status;

    while (1)
    {
        display_prompt();
        fflush(stdout);

        if (getline(&line, &len, stdin) == -1)
        {
            write(STDOUT_FILENO, "\n", 1);
            exit(0);
        }

        line[strlen(line) - 1] = '\0';

        pid = fork();
        if (pid < 0)
        {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            argv_exec[0] = line;
            argv_exec[1] = NULL;
            if (execve(line, argv_exec, NULL) < 0)
            {
                handle_error(argv[0], line);
                exit(1);
            }
        }
        else
        {
            while (wait(&status) != pid)
                ;
        }
    }
    free(line);
    return (0);
}
