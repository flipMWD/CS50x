#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_text(string txt, const int *key);

int main(int ac, char **av)
{
	int key;

	if (!(ac == 2 && (key = atoi(av[1])))) {
		printf("Usage: %s key\n", av[0]);

		return 1;
	}

	key %= 26;
	string input = get_string("plaintext: ");
	convert_text(input, &key);

	printf("ciphertext: %s\n", input);

	return 0;
}

void convert_text(string t, const int *k)
{
	int t_len = strlen(t);

	for (int i = 0; i < t_len; ++i) {
		if (t[i] >= 'A' && t[i] <= 'Z') {
			t[i] = 'A' + (((t[i] - 'A') + *k) % 26);
		} else if (t[i] >= 'a' && t[i] <= 'z') {
			t[i] = 'a' + (((t[i] - 'a') + *k) % 26);
		}
	}
}
