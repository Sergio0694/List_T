#include "..\list_t.h"
#include <stdlib.h>
#include <time.h>

/* ============= Misc ============= */

// Swaps the content of two pointers
static inline void swap_by_pointers(T* n1, T* n2)
{
	int temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

// Returns the base 10 logarithm of a given integer number
static int base10_log(int value)
{
	int log = 0;
	while (value)
	{
		log++;
		value /= 10;
	}
	return log;
}

/* ============================================================================
*  Heapsort
*  ========================================================================= */

// Restores the heap properties of an array by moving down the first element
static void sift_down(T* vector, int start, int end, comparation(*expression)(T, T))
{
	// Temp variables
	int root = start, temp;

	// Iterate while the root has at least one child
	while ((temp = (root << 1) + 1) <= end)
	{
		// Store the first child and the item to swap
		int child = temp;
		int swap = root;

		// If a child is greater than the root, swap the two items
		if (expression(vector[swap], vector[child]) == LOWER) swap = child;
		if ((child + 1 <= end) && (expression(vector[swap], vector[child + 1])) == LOWER)
		{
			swap = child + 1;
		}
		// If the root has the largest element, the soft down operation is concluded
		if (swap == root) return;

		// Perform the sift down and continue
		swap_by_pointers(vector + root, vector + swap);
		root = swap;
	}
}

// Trasnforms a vector into a heap structure, in-place
static void heapify(T* vector, int n, comparation(*expression)(T, T))
{
	int start = (n - 2) / 2;
	while (start >= 0)
	{
		sift_down(vector, start, n - 1, expression);
		start--;
	}
}

// In-place heapsort algorithm >> O(nlogn) as worst case
static void heapsort(T* vector, int n, comparation(*expression)(T, T))
{
	// Rearrange the target vector as a heap
	heapify(vector, n, expression);

	// Begin the actual sorting algorithm
	int end = n - 1;
	while (end > 0)
	{
		// Put the largest value in the first position
		swap_by_pointers(vector + end, vector);

		// Reduce the size of the heap
		end--;

		// Make sure the vector still respects the heap properties
		sift_down(vector, 0, end, expression);
	}
}

/* ============================================================================
*  Insertion sort
*  ========================================================================= */

// Classic in-place insertion sort algorithm >> O(n^2)
static void insertion_sort(T* vector, const size, comparation(*expression)(T, T))
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = i; j < size; j++)
		{
			if (expression(vector[j], vector[i]) == LOWER)
			{
				swap_by_pointers(vector + i, vector + j);
			}
		}
	}
}

/* ============================================================================
*  Quicksort
*  ========================================================================= */

// Partition function based on the Lomuto's Partitioning Algorithm
static int partition(T* vector, int left, int right, comparation(*expression)(T, T))
{
	// Pick a random pivot index and select the pivot item
	int pivot_index = left + (rand() % (right - left + 1));
	T pivot = vector[pivot_index];

	swap_by_pointers(vector + pivot_index, vector + right);
	pivot_index = right;
	int i = left - 1, j;

	for (j = left; j < right; j++)
	{
		comparation result = expression(vector[j], pivot);
		if (result == LOWER || result == EQUAL)
		{
			i++;
			swap_by_pointers(vector + i, vector + j);
		}
	}
	swap_by_pointers(vector + i + 1, vector + pivot_index);
	return i + 1;
}

/* ============================================================================
*  Custom introsort
*  ========================================================================= */

#define MIN_QUICKSORT_SIZE 9

// Custom introsort algorithm that combines quicksort, heapsort and insertion sort
static void main_sort(T* vector, int left, int right, comparation(*expression)(T, T), int depth)
{
	// Stop at the base case and calculate the length of the current vector
	if (left >= right) return;
	int len = right - left + 1;
	
	// If the maximum number of recursive calls has been reached, switch to heapsort
	if (depth == 0) heapsort(vector + left, len, expression);
	else
	{
		// Avoid the recursion and switch to insertion sort with small vectors
		if (len < MIN_QUICKSORT_SIZE)
		{
			insertion_sort(vector + left, len, expression);
		}
		else
		{
			// Classic quicksort step
			int part = partition(vector, left, right, expression);
			main_sort(vector, left, part - 1, expression, depth - 1);
			main_sort(vector, part + 1, right, expression, depth - 1);
		}
	}
}

// Sorts a vector using the custom introsort algorithm
void introsort(T* vector, int len, comparation(*expression)(T, T))
{
	// Parameters check
	if (vector == NULL || len <= 0 || expression == NULL) exit(EXIT_FAILURE);

	// Randomize the rand seed and calculates the max recursion depth
	srand((unsigned)time(NULL));
	int maxdepth = 2 * base10_log(len);

	// Starts the introsort
	main_sort(vector, 0, len - 1, expression, maxdepth);
}