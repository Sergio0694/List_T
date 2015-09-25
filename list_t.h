/* ============================================================================
*  list_t.h
* ============================================================================

*  Author:         (c) 2015 Sergio Pedri and Andrea Salvati
*  License:        See the end of this file for license information
*/

#ifndef LIST_T_H

#define LIST_T_H

/* =================== Define your custom Type here ====================
*  NOTE:
*    You can use a standard value type, a pointer type or a custom
*    type. Just replace "int" with the type you want to use in
*    your program and you will get your List<T> C implementation. */
#ifndef TYPE
#define TYPE int			
#endif

typedef TYPE T;
typedef enum { FALSE, TRUE } bool;
typedef struct listIterator* ListIterator;
typedef struct listBase* List;
typedef List Stack;

/* =====================================================================
*  Generic functions
*  =====================================================================
*  Description:
*    Functions used to create and manage a List.
*  NOTE:
*    Most of these functions work with SIDE EFFECT. */

/* ---------------------------------------------------------------------
*  Create
*  ---------------------------------------------------------------------
*  Description:
*    Creates an empty List. */
List create();

/* ---------------------------------------------------------------------
*  Clear
*  ---------------------------------------------------------------------
*  Description:
*    Removes all the items from the given List. It returns TRUE if
*    the operation was successful or if the List was already empty,
*    FALSE if the List was NULL.
*  NOTE:
*    This will ONLY deallocate the List nodes: if your T is a pointer
*    type you'll have to use the for_each function or another custom
*    function and call the free function to every item in your List.
*  Example (see the LINQ section below):
*    for_each(list, block(item, { free(item); }))
*  Parameters:
*    list ---> The List to clear */
bool clear(List list);

/* ---------------------------------------------------------------------
*  Destroy
*  ---------------------------------------------------------------------
*  Description:
*    Deallocates a List. Returns TRUE if the operation was successful,
*    FALSE if the given List was already NULL.
*  Parameters:
*    list ---> A pointer to the List to deallocate */
bool destroy(List* list);

/* ---------------------------------------------------------------------
*  DestroySeries
*  ---------------------------------------------------------------------
*  Description:
*    This macro will call the destroy_sequence function with the
*    given lists, and will destroy and deallocate each one of them.
*  Example (assuming you have three Lists list1, list2 and list3
*  previously declared inside your code):
*    destroy_series(&list1, &list2, &list3);
*  Parameters:
*    result ---> Pointer to a bool variable used to store the result
*    of the destroy_sequence function: it returns TRUE if the operation
*    was successful, FALSE if the given list was empty.
*    If NULL, this parameter will be ignored
*    ... ---> Pointers to the Lists to destroy */
#define destroy_series(result, ...)          \
List* temp[] = { __VA_ARGS__, 0 };           \
destroy_sequence(result, temp)

// Internal function called by the destroy_series macro.
// Do NOT call this function inside your code: use the above macro.
void destroy_sequence(bool* result, List** pending);

/* ---------------------------------------------------------------------
*  Copy
*  ---------------------------------------------------------------------
*  Description:
*    Copies the source List and returns a new one with the same items.
*  Parameters:
*    source ---> The input List */
List copy(const List source);

/* ---------------------------------------------------------------------
*  CreateRandom
*  ---------------------------------------------------------------------
*  Description:
*    Returns a List where each element is a T cast of a random number
*    between min and max. If the range between min and max is not valid,
*    the function returns NULL.
*  NOTE:
*    This function should ONLY be used when T is integer or another
*    value type. Avoid calling this function when T is a pointer
*    type or a custom type such as a struct.
*  Parameters:
*    length ---> The numbers of elements to create
*    min ---> The minimum value inside the range (included)
*    max ---> The upper value of the desired range (not included) */
List create_random(int length, int min, int max);

/* ---------------------------------------------------------------------
*  CreateFrom
*  ---------------------------------------------------------------------
*  Description:
*    Creates a new List from an array of T elements.
*  Parameters:
*    array ---> The input array
*    size ---> The length of the source array */
List create_from(T* array, int size);

/* ---------------------------------------------------------------------
*  ToArray
*  ---------------------------------------------------------------------
*  Description:
*    Returns an array with all the elements from the input List. Assigns
*    the length of the list to size, otherwise sets it to -1 if the
*    List was NULL or empty, and returns NULL.
*  Parameters:
*    list ---> The source List 
*    size ---> A pointer to an int to store the size of the array */
T* to_array(List list, int* size);

/* ---------------------------------------------------------------------
*  IsEmpty
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE if the List is NULL or empty, FALSE otherwise.
*  Parameters:
*    list ---> The input List */
bool is_empty(List list);

/* ---------------------------------------------------------------------
*  IsElement
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE if the List contains the given element.
*  Parameters:
*    item ---> The element to find inside the List
*    list ---> The input List */
bool is_element(const T item, List list);

/* ---------------------------------------------------------------------
*  GetFirst
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the first element inside the given List.
*    Returns FALSE if the list is NULL or empty.
*  Parameters:
*    list ---> The input List
*    result ---> Pointer to the result T value */
bool get_first(List list, T* result);

/* ---------------------------------------------------------------------
*  GetLast
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the last element of the given List.
*    If the list is NULL or empty, it returns FALSE.
*  Parameters:
*    list ---> The input List
*    result ---> Pointer to the result T value */
bool get_last(List list, T* result);

/* ---------------------------------------------------------------------
*  Get
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the element in a given position inside the input 
*    List. If the list is NULL or empty, it returns FALSE.
*  Parameters:
*    list ---> The input List
*    index ---> The index of the element to return
*    result ---> Pointer to the result T value */
bool get(List list, int index, T* result);

/* ---------------------------------------------------------------------
*  IndexOf
*  ---------------------------------------------------------------------
*  Description:
*    Returns the index of the first occurrence of the given item.
*    If the List doesn't contain the item or if it is NULL,
*    the function returns -1.
*  Parameters:
*    item ---> The element to find inside the List
*    list ---> The input List */
int index_of(const T item, List list);

/* ---------------------------------------------------------------------
*  LastIndexOf
*  ---------------------------------------------------------------------
*  Description:
*    Returns the index of the last occurrence of the given item.
*    If the List doesn't contain the item or if it is NULL,
*    the function returns -1.
*  Parameters:
*    item ---> The element to find inside the List
*    list ---> The input List */
int last_index_of(const T item, List list);

/* ---------------------------------------------------------------------
*  Add
*  ---------------------------------------------------------------------
*  Description:
*    Adds the given element at the end of the input List. It returns
*    TRUE if the operation was successful, FALSE if the List was NULL.
*  Parameters:
*    item ---> The element to add to the List
*    list ---> The List to edit */
bool add(const T item, List list);

/* ---------------------------------------------------------------------
*  AddAt
*  ---------------------------------------------------------------------
*  Description:
*    Inserts an item in a given position inside the List. It returns
*    TRUE if the operation was successful, FALSE if the List was NULL.
*  Parameters:
*    item ---> The item to add
*    list ---> The List to edit
*    index ---> The target index */
bool add_at(const T item, List list, int index);

/* ---------------------------------------------------------------------
*  AddAll
*  ---------------------------------------------------------------------
*  Description:
*    Adds all the items in the second List inside the first one. It
*    returns TRUE if the operation was successful, FALSE if either one
*    of the two Lists was NULL or if the source List was empty.
*  Parameters:
*    target ---> The target List
*    source ---> The source List */
bool add_all(List target, const List source);

/* ---------------------------------------------------------------------
*  Size
*  ---------------------------------------------------------------------
*  Description:
*    Calculates the length of a given List.
*    Returns -1 if the List is NULL.
*  Parameters:
*    list ---> The input List */
int size(List list);

/* ---------------------------------------------------------------------
*  RemoveItem
*  ---------------------------------------------------------------------
*  Description:
*    Removes the first occurrence of the given item from the List.
*    Returns FALSE if the List was either NULL, empty, or if it didn't
*    contain the item to remove.
*  Parameters:
*    item ---> The item to remove
*    list ---> The List to edit */
bool remove_item(const T item, List list);

/* ---------------------------------------------------------------------
*  RemoveAt
*  ---------------------------------------------------------------------
*  Description:
*    Removes the item at a given position inside the List. Returns FALSE
*    if the List was NULL or empty, or if the index was not valid.
*  Parameters:
*    list ---> The list to edit
*    index ---> The index of the element to remove */
bool remove_at(List list, int index);

/* ---------------------------------------------------------------------
*  RemoveAllItems
*  ---------------------------------------------------------------------
*  Description:
*    Removes all the occurrencies of the given item inside the List.
*    Returns -1 if the List was NULL or empty, or if it didn't
*    contain the element to remove, otherwise it returns the
*    number of elements that were removed from the List.
*  Parameters:
*    item ---> The element to remove from the List
*    list ---> The List to edit */
int remove_all_items(const T item, List list);

/* ---------------------------------------------------------------------
*  ReplaceItem
*  ---------------------------------------------------------------------
*  Description:
*    Replaces the first occurrence of the given item inside the List.
*    Returns FALSE if the List was NULL or empty, or if the item was
*    not present inside the List.
*  Parameters:
*    target ---> The element to remove from the List
*    replacement ---> The element to use as a replacement
*    list ---> The List to edit */
bool replace_item(const T target, const T replacement, List list);

/* ---------------------------------------------------------------------
*  ReplaceAt
*  ---------------------------------------------------------------------
*  Description:
*    Replaces the item in the given position with the new item. Returns
*    FALSE if the List was NULL or empty, of if the index was not valid.
*  Parameters:
*    item ---> The raplacement item
*    list ---> The List to edit
*    index ---> The index of the item that will be replaced */
bool replace_at(const T item, List list, int index);

/* ---------------------------------------------------------------------
*  ReplaceAllItems
*  ---------------------------------------------------------------------
*  Description:
*    Replaces all the occurrencies of the given item inside the List.
*    Returns -1 if the List was NULL or empty, or if it didn't
*    contain the element to replace, otherwise it returns the
*    number of elements that were replaced inside the List..
*  Parameters:
*    target ---> The element to remove from the List
*    replacement ---> The element to use when replacing the targets
*    list ---> The List to edit */
int replace_all_items(const T target, const T replacement, List list);

/* ---------------------------------------------------------------------
*  Swap
*  ---------------------------------------------------------------------
*  Description:
*    Inverts the position of two elements inside a List.
*  Parameters:
*    list ---> The List to edit
*    index1 ---> The first index of the element to swap
*    index2 ---> The index of the second element to swap */
bool swap(List list, int index1, int index2);

/* ---------------------------------------------------------------------
*  FormattedPrint
*  ---------------------------------------------------------------------
*  Description:
*    Prints the given List using a custom pattern. The function returns
*    FALSE and prints "NULL list" if the List is NULL, it returns FALSE
*    and prints "Empty list" if the length of the list is 0, otherwise
*    it displays all the items with the following style:
*    item1, item2, item3, ..., itemn and then returns TRUE.
*  Parameters:
*    pattern ---> The pattern to use to print each item
*    list ---> The input List */
bool formatted_print(char* pattern, List list);

/* ---------------------------------------------------------------------
*  Print
*  ---------------------------------------------------------------------
*  Description:
*    Prints all the items inside the List using the same pattern.
*    The function doesn't print anything if the List is empty, and it
*    doesn't use any kind of formatting between two List items.
*    It returns TRUE if the list contained at least one element.
*  Parameters:
*    pattern ---> The pattern to use to print each item
*    list ---> The input list */
bool print(char* pattern, List list);

/* =====================================================================
*  Stack
*  =====================================================================
*  Description:
*    Functions used to manage a Stack.
*  NOTE:
*    The Push and Pop functions work with SIDE EFFECT. */

/* ---------------------------------------------------------------------
*  Push
*  ---------------------------------------------------------------------
*  Description:
*    Adds an element to the top of the Stack. Returns TRUE if the
*    operation was successful, FALSE if the Stack was NULL or empty.
*  Parameters:
*    item ---> The item to add
*    stack ---> The Stack to edit */
bool push(const T item, Stack stack);

/* ---------------------------------------------------------------------
*  Pop
*  ---------------------------------------------------------------------
*  Description:
*    Removes the top element from the Stack and assigns it to result,
*    then returns TRUE. If the Stack is NULL or empty, it returns FALSE.
*  Parameters:
*    stack ---> The Stack to edit 
*     result ---> Pointer to the result T value */
bool pop(Stack stack, T* result);

/* ---------------------------------------------------------------------
*  Peek
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the top element without removing it from the Stack.
*    Returns FALSE if the stack is NULL or empty.
*  Parameters:
*    stack ---> The input Stack 
*    result ---> Pointer to the result T value */
bool peek(Stack stack, T* result);

/* =====================================================================
*  LINQ
*  =====================================================================
*  Description:
*    LINQ-Style (.NET) functions that can be used to get informations 
*    from a List or to create new ones.
*  How-To:
*    Most of these functions take a pointer to function argument: it
*    is possible to create a standard function and pass a pointer to
*    it, or to create a lambda expression using the macro defined 
*    inside this header file.
*  NOTE:
*    All the functions inside this section are FUNCTIONAL and do NOT 
*    edit the input Lists or their elements. */

// Internal macro used as a base to create lambda expressions
#define lambda(return_type, ...)      \
__extension__                         \
({                                    \
    return_type __fn__ __VA_ARGS__    \
    __fn__;                           \
})

/* ---------------------------------------------------------------------
*  Selector
*  ---------------------------------------------------------------------
*  Description:
*    Represents a function with a single parameter that
*    returns a bool. Its body can be multiline as well.
*  Examples (assuming T is int):
*    selector(number, { return number > 10; })
*    selector(number,
*    {
*        if (number < 3) return (number * number) < 9;
*        else return !(number % 2);
*    }) */
#define selector(var_name, func_body) \
lambda(bool, (T var_name) func_body)

/* ---------------------------------------------------------------------
*  Block
*  ---------------------------------------------------------------------
*  Description:
*    Represents a function with a single parameter that
*    performs some operations and returns void.
*  Example (assuming T is int):
*    block(item, { printf("%d ", item); }) */
#define block(var_name, func_body) lambda(void, (T var_name) func_body)

/* ---------------------------------------------------------------------
*  Zipper
*  ---------------------------------------------------------------------
*  Description:
*    Represents a function with a two arguments that creates
*    a new value combining the two parameters and then returns it.
*  Example (assuming T is int):
*    zipper(item1, item2,
*    {
*        if (item1 >= item2) return item1 - item2;
*        return item2 - item1;
*    }) */
#define zipper(var1_name, var2_name, func_body) \
lambda(T, (T var1_name, T var2_name) func_body) \

/* ---------------------------------------------------------------------
*  EqualityTester
*  ---------------------------------------------------------------------
*  Description:
*    Represents a function that takes two arguments and
*    returns true if those arguments are equal, false otherwise.
*  Example:
*    equalityTester(number1, number2, { return number1 == number2; }) */
#define equalityTester(var1_name, var2_name, func_body) \
lambda(bool, (T var1_name, T var2_name) func_body)      \

/* ---------------------------------------------------------------------
*  Comparation
*  ---------------------------------------------------------------------
*  Description:
*    The type returned by a Comparator lambda expression */
typedef enum { EQUAL, GREATER, LOWER } comparation;

/* ---------------------------------------------------------------------
*  Comparator
*  ---------------------------------------------------------------------
*  Description:
*    Represents a function that takes two arguments
*    and returns a different value depending on the relationship
*    between the two. It returns GREATER if arg1 is greater than arg2,
*    LOWER if arg2 is greater than arg1 and EQUAL if the two
*    arguments have the same value.
*  Examples:
*    comparator(number1, number2,
*    {
*        if (number1 > number2) return GREATER;
*        else if (number2 > number1) return LOWER;
*        return EQUAL;
*    }) */
#define comparator(var1_name, var2_name, func_body)       \
lambda(comparation, (T var1_name, T var2_name) func_body) \

/* ---------------------------------------------------------------------
*  ToNumber
*  ---------------------------------------------------------------------
*  Description:
*    Represents a function that takes a single argument and
*    converts it to a numeric value.
*  Example (assuming T is char*):
*    toNumber(item,
*    {
*        T start = item;
*        while(*item != '\0') item++;
*        return item - start;
*    }) */
#define toNumber(var_name, func_body) \
lambda(int, (T var_name) func_body)

/* ---------------------------------------------------------------------
*  Deriver
*  ---------------------------------------------------------------------
*  Description:
*    Represents a function that takes a T parameter and uses it to
*    derive another T argument to return.
*  Example (assuming T is float and math.h has been included):
*    toNumber(item,
*    {
*        return roundf(item);
*    }) */
#define deriver(var_name, func_body) lambda(T, (T var_name) func_body)

/* ---------------------------------------------------------------------
*  FirstOrDefault
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the first element inside the List that
*    satisfies a given condition. It returns FALSE if the List was
*    NULL or empty, TRUE if the operation was successful.
*  Parameters:
*    list ---> The input List
*    result ---> Pointer to the result T value
*    expression ---> Selector lambda expression */
bool first_or_default(List list, T* result, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  LastOrDefault
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the last element inside the List that
*    satisfies a given condition. It returns FALSE if the List was
*    NULL or empty, TRUE if the operation was successful.
*  Parameters:
*    list ---> The input List
*    result ---> Pointer to the result T value
*    expression ---> Selector lambda expression */
bool last_or_default(List list, T* result, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  Count
*  ---------------------------------------------------------------------
*  Description:
*    Returns the number of elements inside the List that
*    satisfy the given expression.
*  Parameters:
*    list ---> The input List
*    expression ---> Selector lambda expression */
int count(List list, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  FirstIndexWhere
*  ---------------------------------------------------------------------
*  Description:
*    Returns the index of the first item inside the List that satisfies
*    the given condition, or -1 if the List was NULL or if the item
*    was not present.
*  Parameters:
*    list ---> The input List
*    expression ---> Selector lambda expression */
int first_index_where(List list, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  LastIndexWhere
*  ---------------------------------------------------------------------
*  Description:
*    Returns the index of the last item inside the List that satisfies
*    the given condition, or -1 if the List was NULL or if the item
*    was not present.
*  Parameters:
*    list ---> The input List
*    expression ---> Selector lambda expression */
int last_index_where(List list, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  Where
*  ---------------------------------------------------------------------
*  Description:
*    Returns a List of all the elements inside the given
*    list that satisfy the given expression.
*    Returns NULL if the List was NULL.
*  Parameters:
*    list ---> The input List
*    expression ---> Selector lambda expression */
List where(List list, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  TakeWhile
*  ---------------------------------------------------------------------
*  Description:
*    Keeps selecting items from the input List while the
*    current item satisfies the given expression, then returns the
*    new List. Returns NULL if the List was NULL.
*  Parameters:
*    list ---> The input List
*    expression ---> Selector lambda expression */
List take_while(List list, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  TakeRange
*  ---------------------------------------------------------------------
*  Description:
*    Returns a List of all the items from the input list that
*    are located between the two given indexes, including them.
*    Returns NULL if the List was NULL or if the indexes were not valid.
*  Parameters:
*    list ---> The input List
*    start ---> The starting index
*    end ---> The final index (should be greater than the first one) */
List take_range(List list, int start, int end);

/* ---------------------------------------------------------------------
*  Concat
*  ---------------------------------------------------------------------
*  Description:
*    Creates a new List by adding all the items from the
*    second List to the items from the first List, and then returns it.
*    Returns NULL if either one of the two Lists is NULL.
*  Parameters:
*    list1 ---> Its items will be the first ones in the new List
*    list2 ---> The second List to add at the end of the first one */
List concat(List list1, List list2);

/* ---------------------------------------------------------------------
*  Zip
*  ---------------------------------------------------------------------
*  Description:
*    Combines two Lists using the given function to
*    create a new item from two different ones from the two Lists.
*    Returns NULL if either one of the two Lists is NULL or empty.
*    If the two Lists have a different length, the new List will have
*    the same number of items of the longer List.
*  Parameters:
*    list1 ---> The first List to combine
*    list2 ---> Should have the same number of items of the first one
*    expression ---> Zipper lambda expression */
List zip(List list1, List list2, T(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Any
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE if at least one element inside the list
*    satisfies the given condition represented by the expression.
*  Parameters:
*    list ---> The input List
*    expression ---> Selector lambda expression */
bool any(List list, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  All
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE only if all the items from the input
*    list satisfy the given condition.
*  Parameters:
*    list ---> The input List
*    expression ---> Selector lambda expression */
bool all(List list, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  Skip
*  ---------------------------------------------------------------------
*  Description:
*    Skips the first n elements from the input List, then
*    creates a new List with the remaining elements and returns it.
*  Parameters:
*    list ---> The input List
*    count ---> The number of List items to skip */
List skip(List list, int count);

/* ---------------------------------------------------------------------
*  SkipWhile
*  ---------------------------------------------------------------------
*  Description:
*    Keeps skipping elements from the given List as long as they
*    satisfy the given condition, then returns the remaining items.
*  Parameters:
*    list ---> The input List
*    expression ---> Selector lambda expression */
List skip_while(List list, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  ForEach
*  ---------------------------------------------------------------------
*  Description:
*    Executes the given function for each item of the given List.
*    Returns TRUE if the operation was successful, FALSE if the List
*    was either NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> Block lambda expression */
bool for_each(List list, void(*expression)(T));

/* ---------------------------------------------------------------------
*  InverseForEach
*  ---------------------------------------------------------------------
*  Description:
*    Executes the given function for each item of the given List,
*    starting from the last one and moving backwards.
*    Returns TRUE if the operation was successful, FALSE if the List
*    was either NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> Block lambda expression */
bool inverse_for_each(List list, void(*expression)(T));

/* ---------------------------------------------------------------------
*  Join
*  ---------------------------------------------------------------------
*  Description:
*    Performs the union operation between two Lists. Returns NULL
*    if either one of the two Lists is NULL.
*  Parameters:
*    list1 ---> The first input List
*    list2 ---> The second List, it can have an arbitrary length
*    expression ---> EqualityTester lambda expression */
List join(List list1, List list2, bool(*expression)(T, T));

/* ---------------------------------------------------------------------
*  JoinWhere
*  ---------------------------------------------------------------------
*  Description:
*    Selects all the items inside the two Lists that satisfy the given
*    condition and then performs the union operation between these two
*    sub Lists. Returns NULL if either one of the two Lists is NULL.
*  Parameters:
*    list1 ---> The first input List
*    list2 ---> The second List, it can have an arbitrary length
*    condition ---> Selector lambda expression
*    expression ---> EqualityTester lambda expression */
List join_where(List list1, List list2, bool(*condition)(T), bool(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Intersect
*  ---------------------------------------------------------------------
*  Description:
*    Performs the intersection between two Lists. Returns NULL
*    if either one of the two Lists is NULL.
*  Parameters:
*    list1 ---> The first input List
*    list2 ---> The second List, it can have an arbitrary length
*    expression ---> EqualityTester lambda expression */
List intersect(List list1, List list2, bool(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Except
*  ---------------------------------------------------------------------
*  Description:
*    Performs the subtraction operation between two Lists.
*    i.e: it returns a new List that contains all the elements that
*    were present inside the first List and not in the second one.
*    Returns NULL if either one of the two Lists is NULL.
*  Parameters:
*    list1 ---> The first input List
*    list2 ---> The second List, it can have an arbitrary length
*    expression ---> EqualityTester lambda expression */
List except(List list1, List list2, bool(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Reverse
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new List that contains all the elements from
*    the given List, but added in reverse order.
*    Returns NULL if the List is NULL or empty.
*  Parameters:
*    list ---> The input List */
List reverse(List list);

/* ---------------------------------------------------------------------
*  ReverseRange
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new List that contains all the items from the source List,
*    with a reversed order for the ones that included inside the
*    given range. Returns NULL if the List is NULL or empty or
*    if the indexes are not valid.
*  Parameters:
*    list ---> The input List
*    start ---> The start index for the reversed section
*    end ---> The index of the last element with the reversed order */
List reverse_range(List list, int start, int end);

/* ---------------------------------------------------------------------
*  Sum
*  ---------------------------------------------------------------------
*  Description:
*    Calculates the sum of all the items inside the List using
*    the given function to get a numeric number from each item.
*    Returns (T)NULL if the list is NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> ToNumber lambda expression */
int sum(List list, int(*expression)(T));

/* ---------------------------------------------------------------------
*  Average
*  ---------------------------------------------------------------------
*  Description:
*    Calculates the average between all the items inside the
*    List using the given function to get a numeric number from each
*    item. Returns (T)NULL if the list is NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> ToNumber lambda expression */
int average(List list, int(*expression)(T));

/* ---------------------------------------------------------------------
*  GetNumericMin
*  ---------------------------------------------------------------------
*  Description:
*    Returns the minimum integer value from the list using
*    the given function to convert each item to a numeric value.
*    Returns (T)NULL if the list is NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> ToNumber lambda expression */
int get_numeric_min(List list, int(*expression)(T));

/* ---------------------------------------------------------------------
*  GetMin
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the item with the lower value, using the given
*    function to compare the elements of the List.
*    Returns FALSE if the List was NULL or empty.
*  Parameters:
*    list ---> The input List
*    result ---> Pointer to the result T value
*    expression ---> Comparator lambda expression */
bool get_min(List list, T* result, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  GetNumericMax
*  ---------------------------------------------------------------------
*  Description:
*    Returns the maximum integer value from the list using
*    the given function to convert each item to a numeric value.
*    Returns (T)NULL if the list is NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> ToNumber lambda expression */
int get_numeric_max(List list, int(*expression)(T));

/* ---------------------------------------------------------------------
*  GetMax
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the item with the higher value, using the given
*    function to compare the elements of the List.
*    Returns FALSE if the List was NULL or empty.
*  Parameters:
*    list ---> The input List
*    result ---> Pointer to the result T value
*    expression ---> Comparator lambda expression */
bool get_max(List list, T* result, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  OrderBy
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new List with all the elements from the input List,
*    ordered using the given expression.
*    This function uses the Bubble Sort algorithm.
*    Returns NULL if the List is NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> Comparator lambda expression */
List order_by(List list, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  OrderByDescending
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new List with all the elements from the input List,
*    ordered using the given expression and in reversed order.
*    This function uses the Bubble Sort algorithm.
*    Returns NULL if the List is NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> Comparator lambda expression */
List order_by_descending(List list, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Distinct
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new List that contains all the single elements
*    from the input List, using the given expression to compare the
*    items. Returns NULL if the List is NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> EqualityTester lambda expression */
List distinct(List list, bool(*expression)(T, T));

/* ---------------------------------------------------------------------
*  CountDistinct
*  ---------------------------------------------------------------------
*  Description:
*    Returns the number of distinct elements inside the given List.
*    If the List is NULL, the function returns -1.
*  Parameters:
*    list ---> The input List
*    expression ---> EqualityTester lambda expression */
int count_distinct(List list, bool(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Single
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the single element inside the List that 
*    satisfies the given condition. If there is more than an item, 
*    if the List is NULL or empty, or if the list doesn't contain
*    an item that satisfies the condition, the function returns FALSE.
*  Parameters:
*    list ---> The input List
*    result ---> Pointer to the result T value
*    expression ---> Selector lambda expression */
bool single(List list, T* result, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  RemoveWhere
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new List with all the elements from the given
*    List except for those that satisfy the current expression.
*    Returns NULL if the List is either NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> Selector lambda expression */
List remove_where(List list, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  ReplaceWhere
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new List where all the items that satisfied the
*    expression were replaced with the given constant value.
*    Returns NULL if the List is either NULL or empty.
*  Parameters:
*    list ---> The input List
*    replacement ---> The value to use when replacing an item
*    expression ---> Selector lambda expression */
List replace_where(List list, const T replacement, bool(*expression)(T));

/* ---------------------------------------------------------------------
*  Derive
*  ---------------------------------------------------------------------
*  Description:
*    Derives a new List applying the given expression to each element.
*    Returns NULL if the List is either NULL or empty.
*  Parameters:
*    list ---> The input List
*    expression ---> Deriver lambda expression */
List derive(List list, T(*expression)(T));

/* ---------------------------------------------------------------------
*  SequenceEquals
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE if two Lists have the same length and their elements
*    are equals and in the same order, FALSE otherwise.
*    If both the Lists are NULL, the function returns TRUE.
*  Parameters:
*    list1 ---> The input List
*    list2 ---> Should have the same length as the first one
*    expression ---> EqualityTester lambda expression */
bool sequence_equals(List list1, List list2, bool(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Trim
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list with all the elements from the first one, and
*    the maximum length adjusted to the given number.
*    Returns NULL if the List is either NULL or empty.
*  Parameters:
*    list ---> The source List
*    length ---> The maximum length for the new List */
List trim(List list, int length);

/* =====================================================================
*  Iterator
*  =====================================================================
*  Description:
*    Functions that create and manage List Iterators.
*  NOTE:
*    Each List can have multiple Iterators, as they are completely
*    indipendent from their original List. Each Iterator is synced with
*    the original state of the List it is referring to: if the 
*    collection is modified the Iterator will become invalid and it will
*    be necessary to restart it. As in foreach loops in other
*    languages, this is done in order to prevent unwanted side effects
*    when using the Iterator. */

/* ---------------------------------------------------------------------
*  GetIterator
*  ---------------------------------------------------------------------
*  Description:
*    Creates and returns a new Iterator for the given List. Returns
*    NULL if the List is NULL or empty.
*  Parameters:
*    list ---> The source List */
ListIterator get_iterator(List list);

/* ---------------------------------------------------------------------
*  DestroyIterator
*  ---------------------------------------------------------------------
*  Description:
*    Deallocates an Iterator and sets it to NULL. It returns True if
*    the operation was successful, FALSE if the iterator was NULL.
*  Parameters:
*    iterator ---> A pointer to the target iterator */
bool destroy_iterator(ListIterator* iterator);

/* ---------------------------------------------------------------------
*  IsSynced
*  ---------------------------------------------------------------------
*  Description:
*    Checks if the target List has been edited after the Iterator
*    was created. Returns FALSE if the Iterator is NULL or out of sync,
*    TRUE otherwise.
*  Parameters:
*    iterator ---> The input Iterator */
bool is_synced(ListIterator iterator);

/* ---------------------------------------------------------------------
*  GetCurrent
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the current item pointed by the Iterator. If the 
*    iterator is NULL or out of sync, the function returns FALSE.
*  Parameters:
*    iterator ---> The input iterator 
*    result ---> Pointer to the result T value */
bool get_current(ListIterator iterator, T* result);

/* ---------------------------------------------------------------------
*  Next
*  ---------------------------------------------------------------------
*  Description:
*    Functions that emulates the standard behaviour of an Iterator in
*    an Object Oriented Language. The first time this function is
*    called, it assigns to result the first element inside the List, 
*    then keeps moving next and assigns the following item each time.
*    If the Iterator is NULL, out of sync, or if there isn't
*    another item left inside the List, the function returns FALSE.
*  NOTE:
*    This function will ONLY start from the first element if the
*    position of the Iterator has never been changed since its
*    creation. Otherwise it starts returning items from its actual 
*    position inside the target List.
*  Parameters:
*    iterator ---> The input iterator
*    result ---> Pointer to the result T value */
bool next(ListIterator iterator, T* result);

/* ---------------------------------------------------------------------
*  CanGoForward
*  ---------------------------------------------------------------------
*  Description:
*    Checks if the Iterator can move forward. It returns FALSE if the
*    iterator is NULL, out of sync, or if there isn't another item left
*    inside the target List, TRUE otherwise.
*  Parameters:
*    iterator ---> The input iterator */
bool can_go_forward(ListIterator iterator);

/* ---------------------------------------------------------------------
*  CanGoBack
*  ---------------------------------------------------------------------
*  Description:
*    Checks if the Iterator can move back. It returns FALSE if the
*    iterator is NULL, out of sync, or if it already points to the 
*    first element of the target List, TRUE otherwise.
*  Parameters:
*    iterator ---> The input iterator */
bool can_go_back(ListIterator iterator);

/* ---------------------------------------------------------------------
*  MoveNext
*  ---------------------------------------------------------------------
*  Description:
*    Moves the Iterator to its next List element, and returns TRUE
*    if the Iterator was not NULL and the operation was successful.
*  Parameters:
*    iterator ---> The input iterator */
bool move_next(ListIterator iterator);

/* ---------------------------------------------------------------------
*  MoveBack
*  ---------------------------------------------------------------------
*  Description:
*    Moves the Iterator to its previous List element, and returns TRUE
*    if the Iterator was not NULL and the operation was successful.
*  Parameters:
*    iterator ---> The input iterator */
bool move_back(ListIterator iterator);

/* ---------------------------------------------------------------------
*  ActualPosition
*  ---------------------------------------------------------------------
*  Description:
*    Returns the current position of the Iterator inside its target List.
*    If the Iterator is NULL or out of sync the function returns -1.
*  Parameters:
*    iterator ---> The input iterator */
int actual_position(ListIterator iterator);

/* ---------------------------------------------------------------------
*  ElementsLeft
*  ---------------------------------------------------------------------
*  Description:
*    Calculates the number of elements inside the list, starting from
*    the actual position of the Iterator. 
*    Returns -1 if it is NULL or out of sync.
*  Parameters:
*    iterator ---> The input iterator */
int elements_left(ListIterator iterator);

/* ---------------------------------------------------------------------
*  ForEachRemaining
*  ---------------------------------------------------------------------
*  Description:
*    Moves the Iterator forward until it reaches the last item inside
*    the List, and performs the given code block for each element.
*    If the operation was successful, it returns the number of times
*    the given expression was executed, otherwise it returns -1.
*  Parameters:
*    iterator ---> The input iterator
*    expression ---> Block lambda expression */
int for_each_remaining(ListIterator iterator, void(*expression)(T));

/* ---------------------------------------------------------------------
*  Restart
*  ---------------------------------------------------------------------
*  Description:
*    Moves the Iterator back to the first position of its target List.
*    It also makes sure the Iterator is synced with the List.
*  Parameters:
*    iterator ---> The input iterator */
bool restart(ListIterator iterator);

#endif

/* Copyright (C) 2015 Sergio Pedri and Andrea Salvati

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