#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shellio.h"

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
		} else if(isalnum(s[0]))
		{
			int n = prscomm(s, dst);
			for(int i = 0; i < n; ++i)
			{
				printf("%s\n", dst[i]);
			}
			printf("❯ ");
		} else
		{
			printf("exit\n");
			return 0;
		}
	}
}
