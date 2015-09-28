/* ============================================================================
*  library_test.c
* ============================================================================

*  Author:         (c) 2015 Sergio Pedri
*  License:        See the end of this file for license information

*  NOTE:
*    This program shows all the functions that are available inside the
*    library. See the instructions inside the list_t.h file
*    on how to compile and use the library with your source codes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Library\list_t.h"

void getch();
void generic_functions_test();
void stack_test();
void LINQ_test();
void iterator_test();
void sorting_benchmarks();

#define BOOL_STRING(value) value ? "True" : "False"
#define NULL_STRING(value) BOOL_STRING(value == NULL)
#define PRINT_BOOL(value) printf(BOOL_STRING(value))
#define PRINT_NULL(value) printf(NULL_STRING(value))
#define PRINT_SIZE printf("\nSIZE: %d", size(test))
#define PRINT_EXPECTED_SIZE_GENERIC(list) \
printf("\nSIZE: %d ---> ", size(list));   \
PRINT_BOOL(size(list) == expected)
#define PRINT_EXPECTED_SIZE PRINT_EXPECTED_SIZE_GENERIC(test)
#define PRINT_EXPECTED_SIZE_STACK PRINT_EXPECTED_SIZE_GENERIC(stack)
#define PRINT_LIST formatted_print("%d", test)

int main(void)
{
	generic_functions_test();
	stack_test();
	LINQ_test();
	iterator_test();
	sorting_benchmarks();
	printf("\n\n======== TESTS COMPLETED ========\n");
	return 0;
}

/* ---------------------------------------------------------------------
*  GenericFunctionsTest
*  ---------------------------------------------------------------------
*  Description:
*    Shows all the functions used to create and manage a list_t. 
*  NOTE:
*    Most of these functions work with SIDE EFFECT. */
void generic_functions_test()
{
	printf("\n======== GENERIC FUNCTIONS ========\n\n");

	// Create random list_t
	list_t test = create_random(10, -20, 30);
	printf(">> Random list with 10 elements from -20 to 30:\n");
	PRINT_LIST;
	int expected = 10;
	PRINT_EXPECTED_SIZE;

	// Copy list_t
	list_t copied = copy(test);
	printf("\n\n>> Copy of the list_t:\n");
	PRINT_LIST;
	PRINT_EXPECTED_SIZE;

	// Destroy list_t
	destroy(&copied);
	printf("\n\n>> Copy destroyed, pointer = NULL ---> ");
	PRINT_NULL(copied);
	int length;

	// DestroySeries
	list_t a, b, c, d;
	a = create_random(20, -20, 20);
	b = create_random(20, -20, 20);
	c = create_random(20, -20, 20);
	d = create_random(20, -20, 20);
	printf("\n\n>> Created 4 temp list_ts, total elements: %d",
		   size(a) + size(b) + size(c) + size(d));
	bool_t confirm;
	destroy_series(&confirm, &a, &b, &c, &d);
	printf("\n\n>> Series destroyed ---> ");
	PRINT_BOOL(confirm);
	printf("\na == NULL: ");
	PRINT_NULL(a);
	printf("\nb == NULL: ");
	PRINT_NULL(b);
	printf("\nc == NULL: ");
	PRINT_NULL(c);
	printf("\nd == NULL: ");
	PRINT_NULL(d);

	// list_t to array
	T* array = to_array(test, &length);
	printf("\n\n>> list_t to array:\n");
	int i = 0;
	for (i = 0; i < length; i++)
	{
		printf("%d", array[i]);
		if (i != length - 1) printf(", ");
	}
	destroy(&test);

	// Array to list_t
	test = create_from(array, length);
	free(array);
	printf("\n\n>> list_t recreated from array:\n");
	PRINT_LIST;
	PRINT_EXPECTED_SIZE;

	// Is empty
	printf("\n\n>> list_t empty: ");
	PRINT_BOOL(is_empty(test));
	printf("\n\n>> Empty list_t created, empty: ");
	list_t empty = create();
	PRINT_BOOL(is_empty(empty));
	destroy(&empty);

	// Add, is element
	add(17, test);
	expected++;
	printf("\n\n>> 17 added to the list_t:\n");
	PRINT_LIST;
	PRINT_EXPECTED_SIZE;
	printf("\n\n>> 17 contained inside the list_t: ");
	PRINT_BOOL(is_element(17, test));
	printf("\n\n>> 200 is element inside the list_t: ");
	PRINT_BOOL(is_element(200, test));

	// Temp value for the get functions
	T temp_value;

	// Get first
	get_first(test, &temp_value);
	printf("\n\n>> Get first: %d", temp_value);

	// Get last
	get_last(test, &temp_value);
	printf("\n\n>> Get last: %d", temp_value);

	// Get
	if (get(test, 6, &temp_value))
	{
		printf("\n\n>> Element at index 6: %d", temp_value);
	}
	else printf("\n\n>> The lists doesn't contain 6 items!");


	// First index
	printf("\n\n>> First index of 10: %d", index_of(10, test));

	// Last index
	printf("\n\n>> Last index of 10: %d", last_index_of(10, test));

	// Add at
	printf("\n\n>> Adding 99 at index 6:\n");
	add_at(99, test, 6);
	PRINT_LIST;
	expected++;
	PRINT_EXPECTED_SIZE;

	// Add all
	list_t toAdd = create_random(3, 1, 10);
	add_all(test, toAdd);
	printf("\n\n>> Created a list_t with 3 elements, added to the first one:\n");
	PRINT_LIST;
	destroy(&toAdd);
	expected += 3;
	PRINT_EXPECTED_SIZE;

	// Size
	printf("\n\n>> Size of the list_t: %d", size(test));

	// Remove item
	printf("\n\n>> Remove first occurrence of the number 17:\n");
	if (remove_item(17, test)) expected--;
	PRINT_LIST;
	PRINT_EXPECTED_SIZE;

	// Remove at
	printf("\n\n>> Remove item at index 5:\n");
	remove_at(test, 5);
	expected--;
	PRINT_LIST;
	PRINT_EXPECTED_SIZE;

	// Remove all items
	printf("\n\n>> Adding 1 at indexes 2, 6 and 8 and twice at the end:\n");
	add_at(1, test, 2);
	add_at(1, test, 6);
	add_at(1, test, 8);
	add(1, test);
	add(1, test);
	expected += 5;
	PRINT_LIST;
	PRINT_EXPECTED_SIZE;
	printf("\n\n>> Removing all occurrencies of 1:\n");
	int counter = remove_all_items(1, test);
	PRINT_LIST;
	printf("\nRemoved %d times", counter);
	expected -= counter;
	PRINT_EXPECTED_SIZE;
	list_t allEquals = create();
	for (i = 0; i < 10; i++) add(10, allEquals);
	printf("\n\n>> Creating a list_t with 10 equal numbers:\n");
	PRINT_LIST;
	printf("\n\n>> Removing all 10s:\n");
	remove_all_items(10, allEquals);
	PRINT_LIST;
	destroy(&allEquals);

	// Replace item
	printf("\n\n>> Adding 10 in position 5:\n");
	add_at(10, test, 5);
	expected++;
	PRINT_LIST;
	PRINT_EXPECTED_SIZE;
	printf("\n\n>> Replacing 10 with 999:\n");
	replace_item(10, 999, test);
	PRINT_LIST;

	// Replace at
	printf("\n\n>> Replace with 100 at index 6:\n");
	replace_at(100, test, 6);
	PRINT_LIST;

	// ReplaceAllItems
	printf("\n\n>> Insert 4 in 3 random positions:\n");
	add_at(4, test, 2);
	add_at(4, test, 5);
	add_at(4, test, 9);
	expected += 3;
	PRINT_LIST;
	PRINT_EXPECTED_SIZE;
	printf("\n\n>> Replace all 4s with 7:\n");
	replace_all_items(4, 7, test);
	PRINT_LIST;

	// Swap
	printf("\n\n>> Swap items in positions 2,5 and 3,7:\n");
	swap(test, 2, 5);
	swap(test, 3, 7);
	PRINT_LIST;
	destroy(&test);
}

/* ---------------------------------------------------------------------
*  stack_tTest
*  ---------------------------------------------------------------------
*  Description:
*    Shows all the functions used to manage a stack_t.
*  NOTE:
*    The Push and Pop functions work with SIDE EFFECT. */
void stack_test()
{
	printf("\n\n======== STACK FUNCTIONS ========\n\n");

	// Push
	stack_t stack = create();
	int i, expected = 10;
	for (i = 0; i < 10; i++) push(i, stack);
	printf(">>Pushed 10 elements from 0 to 9:\n");
	formatted_print("%d", stack);
	PRINT_EXPECTED_SIZE_STACK;

	// Pop
	printf("\n\n>> Pop operation 5 times:\n");
	for (i = 0; i < 5; i++)
	{
		T temp;
		pop(stack, &temp);
		printf("%d", temp);
		if (i != 4) printf(", ");
	}
	expected -= 5;
	PRINT_EXPECTED_SIZE_STACK;

	// Peek
	printf("\n\n>> Actual stack_t:\n");
	formatted_print("%d", stack);
	T temp;
	peek(stack, &temp);
	printf("\n\n>> Top element: %d", temp);
}

#define PRINT_WITH_CHECK(check, item)                  \
if (check == FALSE) printf("Error getting the item");  \
else printf("%d", item)
#define PRINT_TEMP formatted_print("%d", temp)
#define DISPOSE_TEMP destroy(&temp)

/* ---------------------------------------------------------------------
*  LINQTest
*  ---------------------------------------------------------------------
*  Description:
*    Shows all the LINQ-Style (.NET) functions that can be used to get
*    informations from a list_t or to create new ones.
*    Most of these functions take a pointer to function argument: it
*    is possible to create a standard function and pass a pointer to
*    it, or to create a lambda expression using the macro defined inside
*    the header file.
*  NOTE:
*    These functions are FUNCTIONAL and do NOT edit the input list_ts. */
void LINQ_test()
{
	printf("\n\n======== LINQ FUNCTIONS ========\n\n");

	// Create random list
	list_t test = create_random(15, -20, 30);
	printf(">> Random list with 15 elements from -20 to 30:\n");
	PRINT_LIST;

	// FirstOrDefault
	T value;
	bool_t check;
	check = first_or_default(test, &value, selector(item, { return item > 10; }));
	printf("\n\n>> First element > 10: ");
	if (check == FALSE) printf("Error getting the item");
	else printf("%d", value);

	// LastOrDefault
	check = last_or_default(test, &value, selector(item, { return item < 0; }));
	printf("\n\n>> Last element < 0: ");
	PRINT_WITH_CHECK(check, value);

	// Count
	int result = count(test, selector(item, 
	{ 
		return !(item % 2) && item > 0;
	}));
	printf("\n\n>> Even numbers > 0: %d", result);

	// FirstIndexWhere
	result = first_index_where(test, selector(item, 
	{ 
		return !(item % 3) && item > 0; }));
	printf("\n\n>> Index of the first element divisible for 3 and > 0: %d", result);

	// LastIndexWhere
	result = last_index_where(test, selector(item, 
	{ 
		return !(item % 2) && item < 0; 
	}));
	printf("\n\n>> Index of the last even element < 0: %d", result);

	// Where
	list_t temp;
	temp = where(test, selector(item, { return !(item % 3) && item != 0; }));
	printf("\n\n>> list_t of numbers divisible for 3 inside the list_t:\n");
	PRINT_TEMP;
	DISPOSE_TEMP;

	// TakeWhile
	temp = take_while(test, selector(item, 
	{
		if (item >= 0) return item > 10;
		return item < -10;
	}));
	printf("\n\n>> Take elements while they have |value| > 10:\n");
	PRINT_TEMP;
	DISPOSE_TEMP;

	// TakeRange
	temp = take_range(test, 2, 5);
	printf("\n\n>> Take elements from indexes 2 and 5:\n");
	PRINT_TEMP;
	DISPOSE_TEMP;

	// Concat
	temp = create_random(4, 0, 10);
	printf("\n\n>> Random list with 4 elements:\n");
	formatted_print("%d", temp);
	printf("\n\n>> Concat the two list_ts:\n\n");
	list_t two = concat(test, temp);
	formatted_print("%d", two);
	destroy(&two);

	// Zip
	printf("\n\n>> Zip the two lists whith the sum of each couple of items:\n");
	temp = zip(test, temp, zipper(item1, item2, { return item1 + item2; }));
	PRINT_TEMP;
	DISPOSE_TEMP;

	// Any
	printf("\n\n>> Any item in the list that's > 10 && divisible for 3:\n");
	bool_t bool_tResult = any(test, selector(item, { return item > 10 && !(item % 2); }));
	PRINT_BOOL(bool_tResult);

	// All
	printf("\n\n>> All the elements have |value| > 2:\n");
	bool_tResult = all(test, selector(item,
	{
		if (item > 0) return item > 2;
		return item < -2;
	}));
	PRINT_BOOL(bool_tResult);

	// Skip
	printf("\n\n>> Skip the first 6 elements:\n");
	temp = skip(test, 6);
	PRINT_TEMP;
	DISPOSE_TEMP;

	// SkipWhile
	printf("\n\n>> Skip elements while |value| > 2:\n");
	temp = skip_while(test, selector(item, 
	{
		if (item > 0) return item > 2;
		return item < -2;
	}));
	PRINT_TEMP;
	DISPOSE_TEMP;

	// ForEach
	printf("\n\n>> ForEach item print item mod 3:\n");
	for_each(test, block(item, { printf("%d ", item % 3); }));

	// InverseForEach
	printf("\n\n>> Inverse ForEach with the same function:\n");
	inverse_for_each(test, block(item, { printf("%d ", item % 3); }));

	// Join
	temp = create_random(5, 0, 10);
	printf("\n\n>> Created random list_t with 5 items:\n");
	PRINT_TEMP;
	two = join(test, temp, equalityTester(item1, item2, { return item1 == item2; }));
	printf("\n\n>> Join the two list_ts:\n");
	formatted_print("%d", two);
	destroy(&two);

	// JoinWhere
	printf("\n\n>> Join the list_ts only where |value| > 5:\n");
	two = join_where(test, temp, selector(item, 
	{
		if (item > 0) return item > 5;
		return item < -5;
	}), equalityTester(item1, item2, { return item1 == item2; }));
	formatted_print("%d", two);
	destroy(&two);

	// Intersect
	printf("\n\n>> Intersection between the list_ts:\n");
	two = intersect(test, temp, equalityTester(item1, item2, { return item1 == item2; }));
	formatted_print("%d", two);
	destroy(&two);

	// Except
	printf("\n\n>> list_t 1:\n");
	PRINT_LIST;
	printf("\n\n>> list_t 2:\n");
	PRINT_TEMP;
	printf("\n\n>> Subtraction between list_t 2 and list_t 1:\n");
	two = except(temp, test, equalityTester(item1, item2, { return item1 == item2; }));
	formatted_print("%d", two);
	destroy(&two);
	DISPOSE_TEMP;

	// Reverse
	printf("\n\n>> Reverse first list_t:\n");
	temp = reverse(test);
	PRINT_TEMP;
	DISPOSE_TEMP;

	// ReverseRange
	printf("\n\n>> Reverse items from indexes 4 to 9:\n");
	temp = reverse_range(test, 4, 9);
	PRINT_TEMP;
	DISPOSE_TEMP;

	// Sum
	result = sum(test, toNumber(item, { return item; }));
	printf("\n\n>> list_t sum: %d", result);

	// Average
	result = average(test, toNumber(item, { return item; }));
	printf("\n\n>> Average: %d", result);

	// Min
	comparation(*expression)(T, T) = comparator(item1, item2,
	{
		if (item1 > item2) return GREATER;
		else if (item2 > item1) return LOWER;
		else return EQUAL;
	});
	check = get_min(test, &value, expression);
	printf("\n\n>> list_t min: ");
	PRINT_WITH_CHECK(check, value);

	// Max
	check = get_max(test, &value, expression);
	printf("\n\n>> list_t max: ");
	PRINT_WITH_CHECK(check, value);

	// InPlaceOrderBy
	printf("\n\n>> In place order by ascending:\n");
	temp = in_place_order_by(test, expression);
	PRINT_TEMP;
	DISPOSE_TEMP;

	// InPlaceOrderByDescending
	printf("\n\n>> In place order by descending:\n");
	temp = in_place_order_by_descending(test, expression);
	PRINT_TEMP;
	DISPOSE_TEMP;

	printf("\n\n>> Order by ascending:\n");
	temp = order_by(test, expression);
	PRINT_TEMP;
	DISPOSE_TEMP;

	// Distinct
	printf("\n\n>> Distinct items inside the list:\n");
	temp = distinct(test, equalityTester(item1, item2, { return item1 == item2; }));
	PRINT_TEMP;
	DISPOSE_TEMP;

	// Single
	check = single(test, &value, selector(item, 
	{
		if (item > 0) return item > 20;
		return item < -20;
	}));
	printf("\n>> CHECK ---> ");
	printf(check == TRUE ? "TRUE" : "FALSE");
	printf("\n\n>> Single item with |value| > 20: ");
	PRINT_WITH_CHECK(check, value);

	// RemoveWhere
	temp = remove_where(test, selector(item, { return !(item % 3) && item != 0; }));
	printf("\n\n>> Remove items divisible for 3 and != 0:\n");
	PRINT_TEMP;
	DISPOSE_TEMP;

	// ReplaceWhere
	temp = replace_where(test, 0, selector(item, { return !(item % 2) && item != 0; }));
	printf("\n\n>> Replace even numbers != 0 with 0:\n");
	PRINT_TEMP;
	DISPOSE_TEMP;

	// Derive
	temp = derive(test, deriver(item, { return item % 2; }));
	printf("\n\n>> Derive a new list_t where each item is the previous item mod 2:\n");
	PRINT_TEMP;
	
	// SequenceEquals
	printf("\n\n>> The new list_t is equal to the first one:\n");
	bool_tResult = sequence_equals(test, temp, equalityTester(item1, item2, 
	{ 
		return item1 == item2; 
	}));
	PRINT_BOOL(bool_tResult);
	DISPOSE_TEMP;

	// Trim
	printf("\n\n>> Trim the list to a maximum length of 7:\n");
	temp = trim(test, 7);
	PRINT_TEMP;
	DISPOSE_TEMP;
}

/* ---------------------------------------------------------------------
*  IteratorTest
*  ---------------------------------------------------------------------
*  Description:
*    Shows all the functions that use a list_iterator_t.
*  NOTE:
*    None of these functions does SIDE EFFECT. */
void iterator_test()
{
	printf("\n\n======== ITERATOR FUNCTIONS ========\n\n");

	// Create random list_t
	list_t test = create_random(10, -20, 30);
	printf(">> Random list with 10 elements from -20 to 30:\n");
	PRINT_LIST;

	// GetIterator
	list_iterator_t iterator = get_iterator(test);

	// ActualPosition
	printf("\n\n>> New iterator: position %d", actual_position(iterator));

	// CanGoBack
	bool_t result = can_go_back(iterator);
	printf("\n\n>> Can go back: ");
	PRINT_BOOL(result);

	// Remaining
	printf("\n\n>> Remaining positions: %d", elements_left(iterator));

	// Next
	printf("\n\n>> Next item: ");
	T value;
	bool_t check;
	check = next(iterator, &value);
	PRINT_WITH_CHECK(check, value);

	// MoveNext
	move_next(iterator);
	check = get_current(iterator, &value);
	printf("\n\n>> Move next, current item: ");
	PRINT_WITH_CHECK(check, value);

	// CanGoForward
	result = can_go_forward(iterator);
	printf("\n\n>> Can go forward: ");
	PRINT_BOOL(result);

	// ForEachRemaining
	printf("\n\n>> For each remaining item, print its value:\n");
	for_each_remaining(iterator, block(item, { printf("%d ", item); }));

	// Other tests
	get_current(iterator, &value);
	printf("\n\n>> Position and value: %d ---> %d", 
		   actual_position(iterator), value);
	result = can_go_forward(iterator);
	printf("\n\n>> Can go forward: ");
	PRINT_BOOL(result);
	restart(iterator);
	get_current(iterator, &value);
	printf("\n\n>> Restarted, position and value: %d ---> %d",
		   actual_position(iterator), value);
	result = destroy_iterator(&iterator);
	printf("\n\n>> Iterator destroyed, is NULL: ");
	PRINT_BOOL(result);
}

// Returns the local clock time
inline float get_time()
{
	return (float)clock() / CLOCKS_PER_SEC;
}

// Performs a simple benchmark with the two sorting algorithms
void perform_benchmark(int len, comparation(*expression)(T, T))
{
	printf("\n\n>> Test with %d elements", len);
	list_t test, sorted;
	float totalIntro = 0, totalBubble = 0;
	int i;
	for (i = 0; i < 10; i++)
	{
		test = create_random(len, -len, len);
		float start, end;
		start = get_time();
		sorted = order_by(test, expression);
		end = get_time();
		destroy(&sorted);
		totalIntro += end - start;
	}
	printf("\n\n>> Total intro: %f", totalIntro);
	for (i = 0; i < 10; i++)
	{
		test = create_random(len, -len, len);
		float start, end;
		start = get_time();
		sorted = in_place_order_by(test, expression);
		end = get_time();
		destroy(&sorted);
		totalBubble += end - start;
	}
	printf("\n>> Total bubble: %f", totalBubble);
}

/* ---------------------------------------------------------------------
*  SortingBenchmarks
*  ---------------------------------------------------------------------
*  Description:
*    Tests the performances of the two sorting algorithms available */
void sorting_benchmarks()
{
	printf("\n\n======== SORTING BENCHMARKS ========\n\n");

	// Create random list_t
	list_t test, sorted, compare;

	// Comparator used to call the sorting functions
	comparation(*expression)(T, T) = comparator(item1, item2,
	{
		if (item1 > item2) return GREATER;
		else if (item2 > item1) return LOWER;
		else return EQUAL;
	});

	// Introsort basic test
	printf(">> Testing");
	bool_t valid, i;
	for (i = 0; i < 10; i++)
	{
		test = create_random(1000, -500, 500);
		sorted = order_by(test, expression);
		compare = in_place_order_by(test, expression);
		valid = sequence_equals(sorted, compare, equalityTester(n1, n2,
		{
			return n1 == n2;
		}));
		destroy(&sorted);
		destroy(&compare);
		if (!valid) break;
		if (i % 2 == 0) printf(".");
	}
	printf("\n\n>> Success: %s", valid ? "YES! :)" : "NO :'(");
	
	perform_benchmark(1000, expression);
	perform_benchmark(5000, expression);
}

/* Copyright (C) 2015 Sergio Pedri

* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.

* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.

* You should have received a copy of the GNU Lesser General Public
* License along with this library; If not, see http://www.gnu.org/licenses/
*/