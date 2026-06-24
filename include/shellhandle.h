#ifndef SHELLHANDLE_H
#define SHELLHANDLE_H

/*
take a null-terminated string from `src` and tokenize it into separate character pointers in `dst`, then return amount
of tokens.
is used to format input into a format that exec() functions accept.
*/
int prscomm(char *src, char **dst);

/*
handle input commands provided that are supposed to be provided by prscomm().
*/
int handlcomm(char **src);

/*changed STDOUT stream from system standard to file directory specified in src[denom+1]*/
void out2file(char **temp, size_t denom);

/* incase the user didn't bother to hit enter between denominator and commands */
void out2filestr(char *temp, size_t denom);

/*
reverse a string
*/
void strrev(char *s);

/* next two functions are used to sort parameters after '>' denominator. left to the left, right to the right. */
void lefttok(char **src, char *dst, int left);

char *righttok(char **src, char *dst, int left);

#endif
