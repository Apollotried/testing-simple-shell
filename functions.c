#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *_getenv(const char *name)
{
    char *token;
    char *del = "=";
    int i = 0;
    extern char **environ;
    char *temp;

    while (environ[i])
    {
	    temp = strdup(environ[i]);

        token = strtok(temp, del);
        if (strcmp(name, token) == 0)
        {
            return strtok(NULL, del);
        }
	free(temp);
        i++;
    }
    return NULL;
}

char *_getcommand(char *command)
{
    char *path;
    struct stat st;
    char *token;
    char *del = ":";
    char *cmd;

    path = _getenv("PATH");
    token = strtok(path, del);
    while (token)
    {
        cmd = malloc(strlen(token) + 1 + strlen(command) + 1);
        strcpy(cmd, token);
        strcat(cmd, "/");
        strcat(cmd, command);

        if (stat(cmd, &st) == 0)
            return cmd;
        free(cmd);
        token = strtok(NULL, del);
    }
    return NULL;
}

