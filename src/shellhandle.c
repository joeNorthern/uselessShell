#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SH_BLANKS " \t"
#define SH_OPS "><&|"
#define SH_COND_SEQUENCE "&&"
#define SH_INPUT_REDIR ">"
#define SH_COMPLETE 1
#define SH_FAIL -1

static char *const sh_ops[] = {"&&", "|", ">", "<", NULL};
static char *sh_substr[256] = {NULL};
static char sh_cpsr = SH_COMPLETE;

static char* op_match(const char *src);
void sh_debug_input(const char **src);

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

void sh_fd_redirect(char **substr, size_t idx, int oldfd)
{
	int fd = open(*(substr + idx), O_WRONLY | O_CREAT | O_TRUNC, 0666); 
	if(fd < 0) { perror(substr[idx]); _exit(1); }
	if(dup2(fd, STDOUT_FILENO) < 0) { perror("dup2"); _exit(1); }
	close(fd);
}

void sh_ctrlop_lookup(char **substr)
{
	int i = 0;
	int fstatus;
	while(substr[i] != NULL &&(fstatus = strcmp(substr[i], SH_INPUT_REDIR)) != 0)
		++i;

	if(!fstatus)
	{
	// printf("output transferred to %s\n", substr[i+1]);
		substr[i] = NULL;
		sh_fd_redirect(substr, i+1, STDOUT_FILENO);
	}
}

void sh_attempt_fork(char **src)
{
	pid_t pid = fork();
	if(pid < 0) { perror("fork"); return; }
	if(pid == 0)
	{
	// 	printf("I ran\n");
		sh_ctrlop_lookup(src);
		int sh_cpsr = execvp(src[0], src);
		if(sh_cpsr < 0) { printf("Error: execv didn't replace the needed process\n"); _exit(1); }
		_exit(0);
	}
	int status;
	if(waitpid(pid, &status, 0) < 0)
	{
		sh_cpsr = SH_FAIL;
		perror("waitpid");
		return;
	}
	// printf("PID %d exited with status %d\n", pid, status);
	sh_cpsr = SH_COMPLETE;
}

void sh_determine(char **src)
{
	char **word_p = src;
	size_t i = 0;
	while(*word_p != NULL && strcmp(*word_p, SH_COND_SEQUENCE))
	{
		sh_substr[i++] = *word_p;
		word_p++;
	}
	sh_substr[i] = NULL;

	if(sh_substr[0] == NULL)
	{
		printf("Critical error: faulty command\n");
		return;
	}
	sh_attempt_fork(sh_substr);

	if(*word_p != NULL && sh_cpsr == SH_COMPLETE)
		sh_determine(word_p + 1);
}

void sh_debug_input(const char **src)
{
	char const **p = src;
	while(*p != NULL)
		printf("%s\n", *p++);
}

void sh_handle(char **src)
{
	sh_determine(src);
}
