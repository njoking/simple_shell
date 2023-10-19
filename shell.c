#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1) {
        write(STDOUT_FILENO, "#cisfun$ ", 9);
        nread = getline(&line, &len, stdin);
        
        if (nread == -1 && feof(stdin)) {
            exit(EXIT_SUCCESS);
        }
        
        line[nread - 1] = '\0'; // Remove the newline character
        
        pid_t pid = fork();
        if (pid == 0) {
            char *argv[] = {line, NULL};
            execve(line, argv, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("fork");
        }
    }
    free(line);
    return 0;
}
