#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SH_BLANKS " \t"
#define SH_OPS "><&|"

static char *const sh_ops[] = {"&&", "|", ">", "<", NULL};
static char* op_match(const char *src);

size_t sh_tokenize_input(char *src, char **dst)
{
	size_t count = 0;
	char *temp_op = NULL;
	while(*src != '\0')
	{
		src += strspn(src, SH_BLANKS); /* continue skipping till *src doesn't match SH_BLANKS */
		if(*src == '\0') break; /* if hit null terminator, let the flow continue naturally */

		if((temp_op = op_match(src)) != NULL)
		{
			dst[count++] = temp_op; /* if operator found, set it and increment dst to the next args */
			*src = '\0'; /* set current operator as null, hence cutting and safely terminating args before */
			src += strlen(temp_op); /* move src pointer across the size of the relevant operator */
			continue;
		}

		dst[count++] = src; /* point to a new relevant start of input */
		src += strcspn(src, SH_BLANKS SH_OPS); /* loop and return amount of bytes passed till SH_BLANKS/OPS found */
		if(*src != '\0' && strchr(SH_BLANKS, *src) != NULL) /* check wether it's the end OR a newline. Helps line 19  */
             *src++ = '\0'                               	/* exclude trailing newlines. If so, set it as null-term  */
	}                                                       /* and increment the pointer to the next character.       */
	dst[count++] = NULL;
	dst[count] = NULL;
	return count-1;
}

static char* op_match(const char *src)
{
	char *const *p;
	for(p = sh_ops; *p != NULL; ++p)
	{
		if(strncmp(src, *p, strlen(*p)) == 0)
			return *p;
	}
	return NULL;
}

void change_stream(char **src)
{
	;
}

void sh_handle(char **src)
{
<<<<<<< HEAD
	size_t i = 0;
	while(src[i] != NULL)
		printf("%s\n", src[i++]);
=======
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
>>>>>>> 84358cf0f86e14e6ec63dd404db3e591eb1fbe60
}
