/*                 *
 * Data Structures *
 *                 */

/* Arrays                   *
 * O(n)     Insert          *
 * O(log n) Search (Sorted) */

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int *x = malloc(sizeof(int));
	*x = 42; // dereference pointer

	int *list = malloc(3 * sizeof(int));
	if (list == NULL) return 1; // check if memory was allocated successfully

	list[0] = 1;
	list[1] = 2;
	list[2] = 3;

	int *temp = realloc(list, 4 * sizeof(int)); // original buffer, new size
	if (temp == NULL) return 1;

	list = temp; // point old to new block of memory

	temp[3] = 4;

	for (int i = 0; i < 4; ++i)
		printf("%i\n", list[i]);

	free(list);

	return 0;
}


/* Linked Lists *
 * O(n) Insert  *
 * O(n) Search  */

#include <stdlib.h>
#include <stdio.h>

// Typedef allows to refer back to it as node, instead of struct node
typedef struct node
{
	int number;
	struct node *next;
}
node;

int main(void)
{
	node *list = NULL;

	node *n = malloc(sizeof(node));
	if (n == NULL) return 1;

	(*n).number = 2;
	// syntax sugar
	n->number = 3;
	n->next = NULL;

	list = n;

	// advancing the list
	node *temp = list;

	while (temp->next != NULL)
	{
		temp = temp->next;
	}

	// keep linked list sorted
	// call node *n = malloc...
	n->next = list;
	list = n;

	return 0;
}

/* Binary Search Tree *
 * O(log n) Insert    *
 * O(log n) Search    */

#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
	int number;
	struct node *left;
	struct node *right;
}
node;

bool search(node *tree);

int main(void)
{
    int a;

	return 0;
}

bool search(node *tree, int val)
{
	if (tree == NULL)
		return false;

	else if (val < tree->number)
		return search(tree->left);

	else if (val > tree->number)
		return search(tree->right);

	else
		return true;
}

/* Hash Tables       *
 * A hash table is a combination of array and linked lists inside
 *  _
 * |A| -> Albus  |0x32 -> Alice |NULL
 * |B| -> Bigus  |NULL
 * |C| -> Charlie|0x56 -> Claris|0x12 -> Carl|NULL  // three collisions happen
 * |D| -> David  |NULL
 *  ¯
 * O(n)      Insert  *
 * O(n)/Ω(1) Search  */

/* Tries        *
 * It's a tree where each of it's nodes is an array
 * Takes more memory space, but delivers constant time
 *
 *          |A|*B*|C|...|X|Y|Z|     // 26x26x26x...
 *  |A|B|C|...|N|*O*|P|...|
 *              |A|*B*|C|...|
 *
 * O(k) Insert  *    // k = constant equivalent to O(1)
 * O(k) Search  */

/* Queue (FIFO) *
 * enqueue()
 * dequeue()
 * O(n) Insert  *
 * O(n) Search  */

/* Stack (LIFO) *
 * push()
 * pop()
 * O(n) Insert  *
 * O(n) Search  */

/* Dictionary   *
 * Has keys and values, words and page numbers
 * O(n) Insert  *
 * O(n) Search  */
