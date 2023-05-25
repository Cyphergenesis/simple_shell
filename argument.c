#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 1024

int main(void)
{
	char cmd[MAX_LENGTH];
	pid_t pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");

		if (fgets(cmd, MAX_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		cmd[strcspn(cmd, "\n")] = '\0';

		pid = fork();

		if (pid == 0)
		{
			/*Tokenize the command and arguments*/
			char *args[MAX_LENGTH];
			char *tip = strtok(cmd, " ");
			int i = 0;
			while (tip != NULL)
			{
				args[i++] = tip;
				tip = strtok(NULL, " ");
			}
			args[i] = NULL;

			execvp(args[0], args);
			perror("Error");
			exit(1);
		}
		else if (pid < 0)
		{
			perror("Error");
		}
		else
		{
			waitpid(pid, &status, 0);

			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) == 127)
				{
					printf("Command not found.\n");
				}
			}
		}
	}

	return 0;
}

