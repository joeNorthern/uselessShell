#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <../include/macros.h>

int shell_getinput(char *s, size_t maxlen)
{
    int c;
    int n = 0;

    while((c = getchar()) != EOF && n < maxlen-1 && c != '\n')
	{
        s[n++] = c;
	}

	if(c == EOF) return EXIT_SHELL;
	if(isalnum(c))
	{
		printf("Input limit reached, sorry!\n");
		exit(0);
	}
    s[n] = '\0';
    return n;
}
