#include "CS50x.h"
#include <stdio.h>

int main(void)
{
	int n = get_int("Type a number: ");

	if (n % 2 == 0) {
		printf("%d is even.\n", n);
	} else {
		printf("%d is odd.\n", n);
	}
}
