#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024

int getcomm(char *, size_t);

int main(int argc, char **argv)
{
	char s[MAXLINE];
	int i;
	system("clear");
	printf("❯ ");

	while((i = getcomm(s, MAXLINE)) > 0)
	{
		printf("%s\n", s);
		printf("❯ ");
	}
}

int getcomm(char *s, size_t maxlen)
{
	char c;
	int n = 0;

	while((c = getchar()) != EOF && n < maxlen-1 && c != '\n')
	{
		s[n++] = c;
	}
	if(c == '\n')
	{
		*(s+n) = '\0';
	}
	return n;
}
