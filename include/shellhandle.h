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

#endif
