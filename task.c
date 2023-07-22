#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    char *execName;
    (void)argc;
    int status;
    char *del = " \n\t";
    char **array = NULL; // Use a pointer to a pointer to dynamically allocate memory
    char *element;
    char *buffer = NULL;
    size_t n_c = 0;
    int size;
    int i = 0;
    pid_t pid;

    struct stat st;
    execName = argv[0];

    while (1) {
        write(1, "$ ", 2);
        size = getline(&buffer, &n_c, stdin);
        if (size == -1) {
            write(1, "\n", 1);
            exit(1);
        }
        element = strtok(buffer, del);
        i = 0;

        // Dynamically allocate memory for the array
        while (element) {
            array = realloc(array, (i + 1) * sizeof(char *));
            array[i] = element;
            element = strtok(NULL, del);
            i++;
        }
        array = realloc(array, (i + 1) * sizeof(char *));
        array[i] = NULL; // Null-terminate the array

        pid = fork();

        if (pid == 0) {
            // Child process
            execve(array[0], array, NULL);

            perror(execName);
            exit(1);
        } else if (pid < 0) {
            perror("fork");
        } else {
            // Parent process
            wait(&status);
        }
    }

    // Free the dynamically allocated memory before exiting
    for (i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}
