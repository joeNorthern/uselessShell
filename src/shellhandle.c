#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int prscomm(char *src, char *dst[])
{
	char *piece = strtok(src, " ");
	int count = 0;
	int num = 0;
	
	while(piece != NULL)
	{
		dst[count++] = piece;
		piece = strtok(NULL, " ");
		++num;
	}
	dst[count] = NULL;
	return num;
}

int handlcomm(char *src[])
{
	pid_t pid = fork();

	if(pid == 0)
	{
		size_t i = 0;
		while(src[i] != NULL)
		{
			if(memcmp(src[i], ">", 1) == 0)
			{
				printf("it detected >\n");
				_exit(0);
			} else
			{
				_exit(1);
			}
		}
		_exit(1);
	} else if (pid > 0)
	{
		int wstatus;
		wait(&wstatus);
		return wstatus;
	}
	return -1;
}
