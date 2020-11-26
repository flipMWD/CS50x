#include "CS50x.h"
#include <stdio.h>

#define TAX 1.0625

int main(void)
{
	float price = get_float("What's the price? $ ");

	printf("Your total is $ %.2f.\n", price * TAX);
}
