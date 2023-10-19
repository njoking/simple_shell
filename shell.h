#ifndef SHELL_H
#define SHELL_H

/* Include standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Declare external variable */
extern char **environ;

/* Define constants */
#define MAX_BUFFER_SIZE 1024

#endif /* SHELL_H */
