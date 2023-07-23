#include "header.h"

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
