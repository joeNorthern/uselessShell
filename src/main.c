#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <../include/shellhandle.h>
#include <../include/shellio.h>
#include <../include/macros.h>

#define TOTAL_COMMAND_LENGHT 1024

int shell_getinput(char *s, size_t maxlen);

int main()
{
	char s[TOTAL_COMMAND_LENGHT] = {0};
	char *dst[256] = {0};
	ssize_t len = 0;
    printf("\033[2J\033[1;1H");
	printf("$ ");
	
	recursion:
	while((len = shell_getinput(s, TOTAL_COMMAND_LENGHT)) > 0)
	{
		sh_tokenize_input(s, dst);
		sh_handle(dst);

		memset(dst, 0, sizeof(dst));
		memset(s, 0, sizeof(s));
		printf("$ ");
	}
	if(len == 0)
	{
		printf("$ ");
		goto recursion;
	}
	if(len == -1)
		exit(0);
}
