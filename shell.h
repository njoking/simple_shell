#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 100

/* Function Prototypes */
void execute_command(char *line, char *argv0);

#endif /* SHELL_H */
