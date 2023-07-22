#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
int main(){
	while(1)
	{
		int status;
		char *del = " \n\t";
		char *array[10];
		char *element;
		char *buffer = NULL;
		size_t n_c = 0;
		int size;
		int i = 0;
		pid_t pid;

		struct stat st;

		write(1, "$ ", 2);
		size = getline(&buffer, &n_c, stdin);
		if (size == -1)
		{
			write(1, "\n", 1);
			exit(1);
		}
		element = strtok(buffer, del);
		
		while(element)
		{
			array[i] = element;
			element = strtok(NULL, del);
			i++;
		}
		array[i] = NULL;


		pid = fork();

		if (pid == 0)
		{
			execve(array[0], array, NULL);

			perror(array[0]);
			_exit(1);
		}else if (pid < 0)
		{
			perror("fork");
		}
		else{
			wait(&status);
		}
	}
}
