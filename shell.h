#ifndef SHELL_H
#define SHELL_H

/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Constants */
#define MAX_BUFFER_SIZE 1024

/* External environment variable */
extern char **environ;

/* Function prototypes */
void execute_command(char *command);
void execute_external_command(char *args[], int *command_executed);

#endif /* SHELL_H */
