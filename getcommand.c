#include "header.h"

char *_getcommand(char *command) {
    char *path;
    struct stat st;
    char *token;
    char *del = ":";
    char *cmd;
    char *temp;

    if (stat(command, &st) == 0)
	    return command;

    path = _getenv("PATH");
    temp = strdup(path);
    token = strtok(temp, del);

    while (token) {
        cmd = malloc(strlen(token) + 1 + strlen(command) + 1);
        strcpy(cmd, token);
        strcat(cmd, "/");
        strcat(cmd, command);

        if (stat(cmd, &st) == 0) {
            free(temp); 
            return cmd;
        }

        free(cmd);
        token = strtok(NULL, del);
    }

    free(temp); 
    return NULL;
}
