#include <stdio.h>

int main(void)
{
	int nums[3] = {5, 2, 7};
	char ltr[6] = "Hello";

	int arr1_al = sizeof(nums) / sizeof(*nums);
	int arr2_al = sizeof(ltr) / sizeof(ltr[0]);

	int arr1_as = sizeof(nums);
	int arr2_as = sizeof ltr;

	int arr1_es = sizeof *nums;
	int arr2_es = sizeof ltr[0];

	printf("Numbers Array Lenght: %i, Array Size: %i, Elements Size: %i\n"
		"Letters Array Lenght: %i, Array Size: %i, Elements Size: %i\n",
		arr1_al, arr1_as, arr1_es, arr2_al, arr2_as, arr2_es);
}
