#include <stdio.h>
#include <string.h>

#define NAME_LEN 40
#define NUMB_LEN 12

int main(void)
{
	FILE *file = fopen("phonebook.csv", "a");

	char name[NAME_LEN];
	char number[NUMB_LEN];
	int len;

	printf("Name: ");
	fgets(name, NAME_LEN, stdin);
	printf("Number: ");
	fgets(number, NUMB_LEN, stdin);

	/* deal with newline from stdin on submit */
	len = strlen(name);
	if (name[len-1] == '\n') name[len-1] = '\0';

	len = strlen(number);
	if (number[len-1] == '\n') number[len-1] = '\0';

	fprintf(file, "%s,%s\n", name, number);

	fclose(file);

	return 0;
}
