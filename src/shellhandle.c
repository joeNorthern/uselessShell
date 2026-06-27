#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAXLINE 512
#define MAXOP 512
#define MAXCOMM 255 // supposed to be the maximum lenght of one single individual command

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

void strrev(char *s)
{
	int left = 0;
	size_t right = strlen(s)-1;
	char temp;
	
	while(left < right)
	{
		temp = s[left];
		s[left] = s[right];
		s[right] = temp;
		++left; --right;
	}
}

void lefttok(char **src, char *dst, int left)
{
	size_t tempidx = 0;
	while(src[0][left] != '&' && src[0][left] != '\0')
	{
		dst[tempidx++] = src[0][left--];
	}
	dst[tempidx] = '\0';
	strrev(dst);
	dst[--tempidx] = '\0';
}

char *righttok(char **src, char *dst, int right)
{
	size_t tempidx = 0;
	while(src[0][right] != '&' && src[0][right] != '\0')
	{
		dst[tempidx++] = src[0][right++];
	}
	dst[tempidx] = '\0';
	dst = dst+1;

	return dst;
}

void out2filestr(char *src, size_t denom)
{
	int filefd = open(src, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(filefd < 0) { perror("open"); _exit(1); }
	dup2(filefd, STDOUT_FILENO);
	close(filefd);
}

void out2file(char **src, size_t denom)
{
	int filefd = open(src[denom+1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(filefd < 0) { perror("open"); _exit(1); }
	dup2(filefd, STDOUT_FILENO);
	close(filefd);
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
				out2file(src, index);
				
				execvp(src[0], src2);
				perror("execvp");
				_exit(127);
			} else
			{
				size_t denomc = 0;
				while(src[0][denomc] != '\0')
				{
					if(src[0][denomc] == '>')
					{
						char temp[MAXCOMM];
						char *temphold;
						int left, right;
						left = right = denomc;

						out2filestr(righttok(src, temp, left), denomc);
						lefttok(src, temp, left);
						src2[1] = NULL;
						execvp(temp, src2);
						perror("exec");
						_exit(1);
					}
					++denomc;
				}
			}
			++i;
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
