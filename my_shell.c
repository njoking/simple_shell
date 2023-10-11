#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUFFER_SIZE 1024

void execute_command(char *command) {
    // Tokenize the input command
    char *args[MAX_BUFFER_SIZE];
    char *token;
    int i = 0;

    token = strtok(command, " \t\n");
    while (token != NULL) {
        args[i] = token;
        token = strtok(NULL, " \t\n");
        i++;
    }
    args[i] = NULL;

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("Execvp failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        waitpid(pid, NULL, 0);
    }
}

int main() {
    char buffer[MAX_BUFFER_SIZE];

    while (1) {
        // Print shell prompt
        printf("$ ");
        fflush(stdout);

        // Read user input
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        // Remove trailing newline character
        size_t length = strlen(buffer);
        if (buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        // Exit the shell if the user enters 'exit' command
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Execute the command
        execute_command(buffer);
    }

    printf("Exiting shell...\n");
    return 0;
}

