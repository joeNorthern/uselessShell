#ifndef SHELLHANDLE_H
#define SHELLHANDLE_H

/* tokenize input, returns amount of tokens */
size_t sh_tokenize_input(char *src, char **dst);

/* handle tokenized input itself */
void sh_handle(char **);

#endif
