#include <cs50.h>
#include <stdio.h>
#include <math.h>

#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1

int main(void)
{
	float input;

	do {
		input = get_float("Change owed: ");
	}
	while (input < 0);

	/* convert to int to avoid inaccuracies with floats */
	int cents = round(input * 100);
	int coins = 0;

	/* subtract larger value possible from total */
	while (cents > 0) {
		if (cents >= QUARTER) {
			cents -= QUARTER;
		} else if (cents >= DIME) {
			cents -= DIME;
		} else if (cents >= NICKEL) {
			cents -= NICKEL;
		} else {
			cents -= PENNY;
		}

		++coins;
	}

	printf("%d\n", coins);
}
