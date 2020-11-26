#include "CS50x.h"
#include <stdio.h>

int get_int(char* output)
{
	int input;

	printf("%s", output);
	scanf("%d", &input);

	return input;
}

float get_float(char* output)
{
	float input;

	printf("%s", output);
	scanf("%f", &input);

	return input;
}

size_t get_long(char* output)
{
	size_t input;

	printf("%s", output);
	scanf("%ll", &input);

	return input;
}

void get_string(char* output, char* input)
{
	printf("%s", output);
	fgets(input, MAX_STRING_LEN, stdin);
}
