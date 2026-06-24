#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shellio.h"
#include "shellhandle.h"

#define MAXLINE 1024

int main(int argc, char **argv)
{
	char src[MAXLINE] = {0};
	char *dst[MAXLINE] = {0};
	size_t i;
	system("clear");
	printf("❯ ");

	while((i = getcomm(src, MAXLINE)) >= 0)
	{
		if(src[0] == '\n')
		{
			printf("❯ ");
		} else if(isascii(src[0]) && src[0] != '\0')
		{
			int n = prscomm(src, dst);
			if(n == 0)
			{
				printf("❯ ");
			} else if(handlcomm(dst) == 0)
			{
				printf("❯ ");
			} else
			{
				printf("error: %s\n", strerror(1));
				printf("❯ ");
			}
		} else
		{
			printf("exit\n");
			return 0;
		}
	}
}
