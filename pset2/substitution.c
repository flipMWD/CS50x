#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define SUMMATION_2r26 134217726

int key_check(char *str);
void convert_text(string txt, char *key);

int main(int ac, char **av)
{
	int key_validity;

	if (ac == 2) {
		key_validity = key_check(av[1]);

		if (key_validity > 0 && key_validity < 26) {
			printf("Key must contain 26 characters.\n");

			return 1;
		} else if (key_validity <= 0) {
			printf("Usage: %s key\n", av[0]);

			return 1;
		}
	} else {
		printf("Usage: %s key\n", av[0]);

		return 1;
	}

	/* start encryption */
	string input = get_string("plaintext: ");
	convert_text(input, av[1]);

	printf("ciphertext: %s\n", input);

	return 0;
}

int key_check(char *s)
{
	/* cl = current letter */
	int i, cl;
	int binary_sum = 0;
	int k_len = strlen(s);

	for (i = 0; i < k_len; ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			cl = s[i] - ('A' - 1);
		} else if (s[i] >= 'a' && s[i] <= 'z') {
			cl = s[i] - ('a' - 1);
		} else {
			return 0;
		}

		/* the sum of non-repeated numbers as in 2, 4, 8, 16, ..., 67mi
		 * can only be one result, thus avoiding repeated letters */
		binary_sum += pow(2, cl);
	}

	/* Σ of 2^n where i = 1 and n = 26 */
	if (binary_sum == SUMMATION_2r26) {
		return 26;
	} else if (i > 0 && i < 26) {
		return i;
	}

	return 0;
}

void convert_text(string t, char *k)
{
	int t_len = strlen(t);

	for (int i = 0; i < t_len; ++i) {
		if (t[i] >= 'A' && t[i] <= 'Z') {
			/* replace with (key index value(key index position(current letter value))) */
			t[i] = k[(t[i] - 'A')] >= 'a' ? ((k[(t[i] - 'A')] - 'a') + 'A') : k[(t[i] - 'A')];
		} else if (t[i] >= 'a' && t[i] <= 'z') {
			t[i] = k[(t[i] - 'a')] < 'a' ? ((k[(t[i] - 'a')] - 'A') + 'a') : k[(t[i] - 'a')];
		}
	}
}
