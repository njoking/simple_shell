#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 1024

extern char **environ;

void execute_external_command(char *args[], int *command_executed);
void execute_command_from_path(char *args[], int *command_executed,
				char *path_token);
void execute_fork(char *args[], int *command_executed, char *command_path);
void execute_command(char *command);
int main(void);

#endif /* SHELL_H */
