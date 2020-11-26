#include "CS50x.h"
#include <stdio.h>

int main(void)
{
	char name[MAX_STRING_LEN];
	get_string("What's your name?\n", name);

	printf("Hello, %s", name);
	printf("Hello, %10s", name);	// Pad with 5 spaces
	printf("Hello, %*s", 6, name);	// Pad with 6 spaces, could be a var
}
