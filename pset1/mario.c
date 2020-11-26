#include "CS50x.h"
#include <stdio.h>

int get_one_to_eight(void);

int main(void)
{
	int h = get_one_to_eight();

	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < h + 3 + i; ++j)
		{
			if ((j >= h - (i + 1) && j < h) || j >= h + 2)
			{
				putchar('#');
			}
			else
			{
				putchar(' ');
			}
		}

		putchar('\n');
	}

	putchar('\n');
}

int get_one_to_eight(void)
{
	int n;

	do
	{
		n = get_int("Insert integer from 1 to 8: ");
	}
	while (n < 1 || n > 8);

	return n;
}
