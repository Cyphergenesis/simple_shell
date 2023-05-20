#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_ARG 10
#define MAX_PATH_LENGTH 50
#define MAX_PATHS 10

void prompt(char **av, char **env)
{
	char *str = NULL;
	ssize_t gets_char;
	size_t  n = 0;
	int i;
	pid_t pid;
	char *argv[MAX_ARG];
	str = malloc(sizeof(char));

	for (;;)
	{
		if (isatty(0) == 1)
			printf("cisfun$");
		gets_char = getline(&str, &n, stdin);
		if (gets_char == -1)
		{
			free(str);
			exit(1);
		}

		/*remove new line character*/
		for (i = 0; str[i] != '\0'; i++)
		{
			if (str[i] == '\n')
				str[i] = 0;
		}

		/* creates fork process */
		pid = fork();

		/*if  fork fails */
		if (pid == -1)
		{
			perror("fork");
			exit(1);
		}
		
		if (pid == 0)
		{
			if (execve(argv[0], argv, env) == -1)
				printf("%s: No such file or directory", av[0]);
			printf("\n");
			exit(1);
		}

		else
		{
			/* parent process */
			exit(1);
		}
	}
}
