#include "CS50x.h"
#include <stdio.h>

int get_positive_num(void);

int main(void)
{
	int n = get_positive_num();

	printf("%d is a positive number!\n", n);
}

int get_positive_num(void)
{
	int n;

	do {
		n = get_int("Insert a positive integer: ");
	}
	while (n < 1);

	return n;
}
