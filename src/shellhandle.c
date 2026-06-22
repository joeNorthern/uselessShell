#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define MAXLINE 512

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
