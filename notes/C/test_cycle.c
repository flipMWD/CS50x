#include <stdio.h>

int candidate_count = 3;

int locked[3][3] =
{
	{0, 1, 0},
	{0, 0, 1},
	{1, 0, 0}
};

int locked2[3][3] =
{
	{0, 1, 1},
	{0, 0, 0},
	{0, 1, 0}
};


int cycle_check(int f, int t)
{
    int c = 0;

    for (int i = 0; i < candidate_count; ++i)
    {
        if (locked[f][i])
        {
            if (i == t)
            {
                return 1;
            }

            else
            {
                c = cycle_check(i, t);
            }
        }
    }

    if (c) return 1;

    return 0;
}

int main(void)
{
	if (cycle_check(1, 0))
		printf("Cycle\n");
	else
		printf("No Cycle\n");

	if (cycle_check(0, 2))
		printf("Cycle\n");
	else
		printf("No Cycle\n");

	if (cycle_check(2, 1))
		printf("Cycle\n");
	else
		printf("No Cycle\n");

	return 0;
}
