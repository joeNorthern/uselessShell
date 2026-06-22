#include <stdio.h>
#include <stdlib.h>

int getcomm(char *s, size_t maxlen)
{
    int c;
    int n = 0;

    while((c = getchar()) != EOF && n < maxlen-1 && c != '\n')
    {
        s[n++] = c;
    }
    s[n] = '\0';
    return n;
}
