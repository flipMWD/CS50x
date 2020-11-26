#include <stdio.h>

#define SIG_LENGTH 3

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	FILE *file = fopen(av[1], "r");

	if (file == NULL)
		return 2;
	
	unsigned char bytes[SIG_LENGTH];

	/* read to buffer, size, count, stream */
	fread(bytes, sizeof *bytes, SIG_LENGTH, file);

	/* all jpeg images start with 0xff 0xd8 0xff */
	if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff) {
		printf("Maybe a .jpg\n");
	} else {
		printf("Definetely not a .jpg\n");
	}

	return 0;
}
