#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <../include/shellhandle.h>
#include <../include/shellio.h>
#include <../include/macros.h>

#define TOTAL_COMMAND_LENGHT 1024

int shell_getinput(char *s, size_t maxlen);
void reset_arrays(char *arrayA, size_t lenA, char **arrayB, size_t countB);

int main()
{
	char s[TOTAL_COMMAND_LENGHT] = {0};
	char *dst[256] = {0};
	ssize_t len = 0;

    printf("\033[2J\033[1;1H");
	printf("$ ");

	while(1)
	{
		if((len = shell_getinput(s, TOTAL_COMMAND_LENGHT)) > 0)
		{
			sh_tokenize_input(s, dst);
			sh_handle(dst);
			reset_arrays(s, sizeof(s), dst, sizeof(dst) / sizeof(dst[0]));
			printf("$ ");
		}
		if(len == 0) printf("$ ");
		if(len == -1) exit(0);
	}
}

void reset_arrays(char *arrayA, size_t lenA, char **arrayB, size_t countB)
{
    memset(arrayA, 0, lenA);
    memset(arrayB, 0, countB * sizeof(*arrayB));
}
