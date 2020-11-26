#include "CS50x.h"
#include <stdio.h>

int main(void)
{
	int age = get_int("What's your age? ");

	printf("You're at least %d days old.\n", age * 365);
}
