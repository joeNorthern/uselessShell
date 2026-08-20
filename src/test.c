#include <stdio.h>
#include <string.h>
#define SH_BLANKS " \t"
int main()
{
	const char *p = "ls > text.txt";
	p += strspn(p, SH_BLANKS);
	p += strcspn(p, SH_BLANKS);
	printf("%s\n", p);
	return 0;
}

// > text.txt
