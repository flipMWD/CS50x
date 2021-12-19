#include <cs50.h>
#include <stdio.h>
#include <math.h>

float calc_avg_per_words(int val, int words);
float coleman_liau_index(float l_avg, float s_avg);

int main(void)
{
	string input = get_string("Text: ");
	int l, w, s;
	bool in_word = false;
	float cl_index;

	l = w = s = 0;

	for (int i = 0; input[i] != '\0'; ++i) {
		if ((input[i] >= 'A' && input[i] <= 'Z') ||
			(input[i] >= 'a' && input[i] <= 'z')) {
			++l;

			if (!in_word) {
				in_word = true;
			}

			continue;
		} else if (in_word) {
			/* only triggers for hyphenated compound words and "apostrophes" using single quotes in the middle of a word*/
			if (input[i] == '-' || input[i] == '\'') {
				continue;
			}

			++w;
		}

		/* new condition block */
		if (input[i] == '.' || input[i] == '!' || input[i] == '?') {
			++s;
		}

		in_word = false;
	}

	cl_index = coleman_liau_index(calc_avg_per_words(l, w), calc_avg_per_words(s, w));

	if (cl_index < 1) {
		printf("Before Grade 1\n");
	} else if (cl_index > 16) {
		printf("Grade 16+\n");
	} else {
		printf("Grade %d\n", (int) round(cl_index));
	}
}

float calc_avg_per_words(int val, int words)
{
	return ((float) val * 100) / (float) words;
}

float coleman_liau_index(float l_avg, float s_avg)
{
	return (0.0588 * l_avg) - (0.296 * s_avg) - 15.8;
}
