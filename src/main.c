#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shellio.h"
#include "shellhandle.h"

#define MAXLINE 1024

int main(int argc, char **argv)
{
	char s[MAXLINE];
	char *dst[MAXLINE];
	int i;
	system("clear");
	printf("❯ ");

	while((i = getcomm(s, MAXLINE)) >= 0)
	{
		if(*s == '\n')
		{
			printf("❯ ");
		} else if(isascii(s[0]) && s[0] != '\0')
		{
			prscomm(s, dst);
			if(handlcomm(dst) == 0)
			{
				printf("good shit\n");
			}
			printf("❯ ");
		} else
		{
			printf("exit\n");
			return 0;
		}
	}
}
