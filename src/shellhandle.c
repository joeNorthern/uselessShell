#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SH_BLANKS " \t"
#define SH_OPS "><&|"
#define SH_COND_SEQUENCE "&&"
#define SH_COMPLETE 1
#define SH_FAIL -1

static char *const sh_ops[] = {"&&", "|", ">", "<", NULL};
static char *sh_substr[256] = {NULL};
static char sh_cpsr = 0;

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
             *src++ = '\0';                               	/* exclude trailing newlines. If so, set it as null-term  */
	}                                                       /* and increment the pointer to the next character.       */
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

void change_stdout(char *src)
{
	;
}



void sh_determine(const char **src)
{
	const char **word_p = src;
	size_t i = 0;
	while(*word_p != NULL && strcmp(*word_p, SH_COND_SEQUENCE) != 0)
	{
		sh_substr[i++] = *word_p;
		word_p++;
	} 
	sh_substr[i] = NULL;

	if(*word_p == NULL)
	{
		; /* total control transfer to exevp goes here */
	} else
	{
		/*
		a function that will parse the current relevant command goes here
		it should return SH_COMPLETE, and then we will increment
		word_p again. Recursed

		*/
		word_p++; /* saving frame for post condition sequence commands */
		printf("--------------------\n");
		sh_determine(word_p);
	}
}

void sh_debug_input(const char **src)
{
	char const **p = src;
	while(*p != NULL)
		printf("%s\n", *p++);
}

void sh_handle(const char **src)
{
	sh_determine(src);
}
