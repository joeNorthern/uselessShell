#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SH_BLANKS " \t"
#define SH_OPS "><&|"

static char *const sh_ops[] = {"&&", "|", ">", "<", NULL};
static char* op_match(const char *src);

size_t sh_tokenize_input(char *src, char **dst)
{
	size_t count = 0;
	char *temp_op = NULL;
	while(*src != '\0')
	{
		src += strspn(src, SH_BLANKS); /* continue skipping till *src doesn't match SH_BLANKS */
		if(*src == '\0') break; /* if hit null terminator, let the flow continue naturally */

		if((temp_op = op_match(src)) != NULL)
		{
			dst[count++] = temp_op; /* if operator found, set it and increment dst to the next args */
			*src = '\0'; /* set current operator as null, hence cutting and safely terminating args before */
			src += strlen(temp_op); /* move src pointer across the size of the relevant operator */
			continue;
		}

		dst[count++] = src; /* point to a new relevant start of input */
		src += strcspn(src, SH_BLANKS SH_OPS); /* loop and return amount of bytes passed till SH_BLANKS/OPS found */
		if(*src != '\0' && strchr(SH_BLANKS, *src) != NULL) /* check wether it's the end OR a newline. Helps line 19  */
             *src++ = '\0'                               	/* exclude trailing newlines. If so, set it as null-term  */
	}                                                       /* and increment the pointer to the next character.       */
	dst[count++] = NULL;
	dst[count] = NULL;
	return count-1;
}

static char* op_match(const char *src)
{
	char *const *p;
	for(p = sh_ops; *p != NULL; ++p)
	{
		if(strncmp(src, *p, strlen(*p)) == 0)
			return *p;
	}
	return NULL;
}

void change_stream(char **src)
{
	;
}

void sh_handle(char **src)
{
	size_t i = 0;
	while(src[i] != NULL)
		printf("%s\n", src[i++]);
}
