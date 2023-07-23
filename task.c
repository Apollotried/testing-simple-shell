#include "header.h"
int main(int argc, char *argv[]) {
    char *execName;
    (void)argc;
    int status;
    char *del = " \n\t";
    char **array = NULL; 
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

        while (element) {
            array = realloc(array, (i + 1) * sizeof(char *));
            array[i] = element;
            element = strtok(NULL, del);
            i++;
        }
        array = realloc(array, (i + 1) * sizeof(char *));
        array[i] = NULL;

        pid = fork();

        if (pid == 0) {
            execve(array[0], array, NULL);

            perror(execName);
            exit(1);
        } else if (pid < 0) {
            perror("fork");
        } else {
            wait(&status);
        }
    }

    for (i = 0; array[i] != NULL; i++) {
        free(array[i]);
    }
    free(array);

    return 0;
}
