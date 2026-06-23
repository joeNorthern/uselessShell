#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAXLINE 512
#define MAXOP 512

int prscomm(char *src, char *dst[])
{
	int i = 0;
	while(src[i] != '\0' && isspace((int)src[i]))
	{
		++i;
	}
	char *piece = strtok(src+i, " \n\t");
	int count = 0;
	int num = 0;
	
	while(piece != NULL)
	{
		dst[count++] = piece;
		piece = strtok(NULL, " \n\t");
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
		char *src2[MAXLINE];
		size_t index = 0;

		while(src[i] != NULL)
		{
			if(memcmp(src[i], ">", 1) == 0)
			{	
				int n = i;

				do {
					src2[index++] = src[n];
				} while(n > 0 && --n);
				src2[index] = NULL;

				int filefd = open(src[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if(filefd < 0) { perror("open"); _exit(1); }
				dup2(filefd, STDOUT_FILENO);
				close(filefd);
				
				execvp(src[0], src2);
				perror("execvp");
				_exit(127);
			} else
			{
				++i;
			}
		}
		int a = 0;
		while(src[a] != NULL)
		{
			src2[index++] = src[a];
			a++;
		}
		src2[a] = NULL;
		execvp(src[0], src2);
		perror("exec");
		_exit(1);
	} else if (pid > 0)
	{
		int wstatus;
		wait(&wstatus);
		return wstatus;
	}
	return -1;
}
