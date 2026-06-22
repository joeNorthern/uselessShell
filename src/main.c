#include <stdio.h>
#include <stdlib.h>
#include "shellio.h"

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
