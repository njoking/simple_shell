#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;  // Declare the external environment variable

#define MAX_BUFFER_SIZE 1024

void execute_command(char *command) {
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

    // Handling built-in 'env' command
    if (strcmp(args[0], "env") == 0) {  // ADDED
        for (i = 0; environ[i] != NULL; i++) {
            printf("%s\n", environ[i]);
        }
        return;
    }

    char *path = getenv("PATH");
    if (path == NULL) {
        perror("Failed to get PATH");
        return;
    }
    char *path_copy = strdup(path);
    char *path_token = strtok(path_copy, ":");
    int command_executed = 0;  // Flag to track if command was executed
    while (path_token != NULL) {
        char command_path[MAX_BUFFER_SIZE];
        snprintf(command_path, sizeof(command_path), "%s/%s", path_token, args[0]);

        if (access(command_path, X_OK) == 0) {
            pid_t pid = fork();
            if (pid < 0) {
                perror("Fork failed");
            } else if (pid == 0) {
                if (execv(command_path, args) == -1) {
                    perror("Execv failed");
                    exit(EXIT_FAILURE);
                }
            } else {
                waitpid(pid, NULL, 0);
                command_executed = 1;  // Command found and executed
                break;
            }
        }
        path_token = strtok(NULL, ":");
    }

    // If command wasn't found and executed, print error message
    if (!command_executed) {
        fprintf(stderr, "%s: command not found\n", args[0]);
    }

    free(path_copy);
}

int main() {
    char buffer[MAX_BUFFER_SIZE];

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }

        size_t length = strlen(buffer);
        if (buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        execute_command(buffer);
    }

    printf("Exiting shell...\n");
    return 0;
}
