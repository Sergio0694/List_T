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

// =================== Public types ====================
typedef TYPE T;
typedef enum { FALSE, TRUE } bool_t;
typedef struct listIterator* list_iterator_t;
typedef struct listBase* list_t;
typedef list_t stack_t;

/* =====================================================================
*  Generic functions
*  =====================================================================
*  Description:
*    Functions used to create and manage a list_t.
*  NOTE:
*    Most of these functions work with SIDE EFFECT. */

/* ---------------------------------------------------------------------
*  Create
*  ---------------------------------------------------------------------
*  Description:
*    Creates an empty list_t. */
list_t create();

/* ---------------------------------------------------------------------
*  Clear
*  ---------------------------------------------------------------------
*  Description:
*    Removes all the items from the given list_t. It returns TRUE if
*    the operation was successful or if the list_t was already empty,
*    FALSE if the list_t was NULL.
*  NOTE:
*    This will ONLY deallocate the list_t nodes: if your T is a pointer
*    type you'll have to use the for_each function or another custom
*    function and call the free function to every item in your list_t.
*  Example (see the LINQ section below):
*    for_each(list, block(item, { free(item); }))
*  Parameters:
*    list ---> The list_t to clear */
bool_t clear(list_t list);

/* ---------------------------------------------------------------------
*  Destroy
*  ---------------------------------------------------------------------
*  Description:
*    Deallocates a list_t. Returns TRUE if the operation was successful,
*    FALSE if the given list_t was already NULL.
*  Parameters:
*    list ---> A pointer to the list_t to deallocate */
bool_t destroy(list_t* list);

/* ---------------------------------------------------------------------
*  DestroySeries
*  ---------------------------------------------------------------------
*  Description:
*    This macro will call the destroy_sequence function with the
*    given lists, and will destroy and deallocate each one of them.
*  Example (assuming you have three list_ts list1, list2 and list3
*  previously declared inside your code):
*    destroy_series(&list1, &list2, &list3);
*  Parameters:
*    result ---> Pointer to a bool_t variable used to store the result
*    of the destroy_sequence function: it returns TRUE if the operation
*    was successful, FALSE if the given list was empty.
*    If NULL, this parameter will be ignored
*    ... ---> Pointers to the list_ts to destroy */
#define destroy_series(result, ...)          \
list_t* temp[] = { __VA_ARGS__, 0 };           \
destroy_sequence(result, temp)

// Internal function called by the destroy_series macro.
// Do NOT call this function inside your code: use the above macro.
void destroy_sequence(bool_t* result, list_t** pending);

/* ---------------------------------------------------------------------
*  Copy
*  ---------------------------------------------------------------------
*  Description:
*    Copies the source list_t and returns a new one with the same items.
*  Parameters:
*    source ---> The input list_t */
list_t copy(const list_t source);

/* ---------------------------------------------------------------------
*  CreateRandom
*  ---------------------------------------------------------------------
*  Description:
*    Returns a list_t where each element is a T cast of a random number
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
list_t create_random(int length, int min, int max);

/* ---------------------------------------------------------------------
*  CreateFrom
*  ---------------------------------------------------------------------
*  Description:
*    Creates a new list_t from an array of T elements.
*  Parameters:
*    array ---> The input array
*    size ---> The length of the source array */
list_t create_from(T* array, int size);

/* ---------------------------------------------------------------------
*  ToArray
*  ---------------------------------------------------------------------
*  Description:
*    Returns an array with all the elements from the input list_t. Assigns
*    the length of the list to size, otherwise sets it to -1 if the
*    list_t was NULL or empty, and returns NULL.
*  Parameters:
*    list ---> The source list_t 
*    size ---> A pointer to an int to store the size of the array */
T* to_array(list_t list, int* size);

/* ---------------------------------------------------------------------
*  IsEmpty
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE if the list_t is NULL or empty, FALSE otherwise.
*  Parameters:
*    list ---> The input list_t */
bool_t is_empty(list_t list);

/* ---------------------------------------------------------------------
*  IsElement
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE if the list_t contains the given element.
*  Parameters:
*    item ---> The element to find inside the list_t
*    list ---> The input list_t */
bool_t is_element(const T item, list_t list);

/* ---------------------------------------------------------------------
*  GetFirst
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the first element inside the given list_t.
*    Returns FALSE if the list is NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    result ---> Pointer to the result T value */
bool_t get_first(list_t list, T* result);

/* ---------------------------------------------------------------------
*  GetLast
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the last element of the given list_t.
*    If the list is NULL or empty, it returns FALSE.
*  Parameters:
*    list ---> The input list_t
*    result ---> Pointer to the result T value */
bool_t get_last(list_t list, T* result);

/* ---------------------------------------------------------------------
*  Get
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the element in a given position inside the input 
*    list_t. If the list is NULL or empty, it returns FALSE.
*  Parameters:
*    list ---> The input list_t
*    index ---> The index of the element to return
*    result ---> Pointer to the result T value */
bool_t get(list_t list, int index, T* result);

/* ---------------------------------------------------------------------
*  IndexOf
*  ---------------------------------------------------------------------
*  Description:
*    Returns the index of the first occurrence of the given item.
*    If the list_t doesn't contain the item or if it is NULL,
*    the function returns -1.
*  Parameters:
*    item ---> The element to find inside the list_t
*    list ---> The input list_t */
int index_of(const T item, list_t list);

/* ---------------------------------------------------------------------
*  LastIndexOf
*  ---------------------------------------------------------------------
*  Description:
*    Returns the index of the last occurrence of the given item.
*    If the list_t doesn't contain the item or if it is NULL,
*    the function returns -1.
*  Parameters:
*    item ---> The element to find inside the list_t
*    list ---> The input list_t */
int last_index_of(const T item, list_t list);

/* ---------------------------------------------------------------------
*  Add
*  ---------------------------------------------------------------------
*  Description:
*    Adds the given element at the end of the input list_t. It returns
*    TRUE if the operation was successful, FALSE if the list_t was NULL.
*  Parameters:
*    item ---> The element to add to the list_t
*    list ---> The list_t to edit */
bool_t add(const T item, list_t list);

/* ---------------------------------------------------------------------
*  AddAt
*  ---------------------------------------------------------------------
*  Description:
*    Inserts an item in a given position inside the list_t. It returns
*    TRUE if the operation was successful, FALSE if the list_t was NULL.
*  Parameters:
*    item ---> The item to add
*    list ---> The list_t to edit
*    index ---> The target index */
bool_t add_at(const T item, list_t list, int index);

/* ---------------------------------------------------------------------
*  AddAll
*  ---------------------------------------------------------------------
*  Description:
*    Adds all the items in the second list_t inside the first one. It
*    returns TRUE if the operation was successful, FALSE if either one
*    of the two list_ts was NULL or if the source list_t was empty.
*  Parameters:
*    target ---> The target list_t
*    source ---> The source list_t */
bool_t add_all(list_t target, const list_t source);

/* ---------------------------------------------------------------------
*  Size
*  ---------------------------------------------------------------------
*  Description:
*    Calculates the length of a given list_t.
*    Returns -1 if the list_t is NULL.
*  Parameters:
*    list ---> The input list_t */
int size(list_t list);

/* ---------------------------------------------------------------------
*  RemoveItem
*  ---------------------------------------------------------------------
*  Description:
*    Removes the first occurrence of the given item from the list_t.
*    Returns FALSE if the list_t was either NULL, empty, or if it didn't
*    contain the item to remove.
*  Parameters:
*    item ---> The item to remove
*    list ---> The list_t to edit */
bool_t remove_item(const T item, list_t list);

/* ---------------------------------------------------------------------
*  RemoveAt
*  ---------------------------------------------------------------------
*  Description:
*    Removes the item at a given position inside the list_t. Returns FALSE
*    if the list_t was NULL or empty, or if the index was not valid.
*  Parameters:
*    list ---> The list to edit
*    index ---> The index of the element to remove */
bool_t remove_at(list_t list, int index);

/* ---------------------------------------------------------------------
*  RemoveAllItems
*  ---------------------------------------------------------------------
*  Description:
*    Removes all the occurrencies of the given item inside the list_t.
*    Returns -1 if the list_t was NULL or empty, or if it didn't
*    contain the element to remove, otherwise it returns the
*    number of elements that were removed from the list_t.
*  Parameters:
*    item ---> The element to remove from the list_t
*    list ---> The list_t to edit */
int remove_all_items(const T item, list_t list);

/* ---------------------------------------------------------------------
*  ReplaceItem
*  ---------------------------------------------------------------------
*  Description:
*    Replaces the first occurrence of the given item inside the list_t.
*    Returns FALSE if the list_t was NULL or empty, or if the item was
*    not present inside the list_t.
*  Parameters:
*    target ---> The element to remove from the list_t
*    replacement ---> The element to use as a replacement
*    list ---> The list_t to edit */
bool_t replace_item(const T target, const T replacement, list_t list);

/* ---------------------------------------------------------------------
*  ReplaceAt
*  ---------------------------------------------------------------------
*  Description:
*    Replaces the item in the given position with the new item. Returns
*    FALSE if the list_t was NULL or empty, of if the index was not valid.
*  Parameters:
*    item ---> The raplacement item
*    list ---> The list_t to edit
*    index ---> The index of the item that will be replaced */
bool_t replace_at(const T item, list_t list, int index);

/* ---------------------------------------------------------------------
*  ReplaceAllItems
*  ---------------------------------------------------------------------
*  Description:
*    Replaces all the occurrencies of the given item inside the list_t.
*    Returns -1 if the list_t was NULL or empty, or if it didn't
*    contain the element to replace, otherwise it returns the
*    number of elements that were replaced inside the list_t..
*  Parameters:
*    target ---> The element to remove from the list_t
*    replacement ---> The element to use when replacing the targets
*    list ---> The list_t to edit */
int replace_all_items(const T target, const T replacement, list_t list);

/* ---------------------------------------------------------------------
*  Swap
*  ---------------------------------------------------------------------
*  Description:
*    Inverts the position of two elements inside a list_t.
*  Parameters:
*    list ---> The list_t to edit
*    index1 ---> The first index of the element to swap
*    index2 ---> The index of the second element to swap */
bool_t swap(list_t list, int index1, int index2);

/* ---------------------------------------------------------------------
*  FormattedPrint
*  ---------------------------------------------------------------------
*  Description:
*    Prints the given list_t using a custom pattern. The function returns
*    FALSE and prints "NULL list" if the list_t is NULL, it returns FALSE
*    and prints "Empty list" if the length of the list is 0, otherwise
*    it displays all the items with the following style:
*    item1, item2, item3, ..., itemn and then returns TRUE.
*  Parameters:
*    pattern ---> The pattern to use to print each item
*    list ---> The input list_t */
bool_t formatted_print(char* pattern, list_t list);

/* ---------------------------------------------------------------------
*  Print
*  ---------------------------------------------------------------------
*  Description:
*    Prints all the items inside the list_t using the same pattern.
*    The function doesn't print anything if the list_t is empty, and it
*    doesn't use any kind of formatting between two list_t items.
*    It returns TRUE if the list contained at least one element.
*  Parameters:
*    pattern ---> The pattern to use to print each item
*    list ---> The input list */
bool_t print(char* pattern, list_t list);

/* =====================================================================
*  stack_t
*  =====================================================================
*  Description:
*    Functions used to manage a stack_t.
*  NOTE:
*    The Push and Pop functions work with SIDE EFFECT. */

/* ---------------------------------------------------------------------
*  Push
*  ---------------------------------------------------------------------
*  Description:
*    Adds an element to the top of the stack_t. Returns TRUE if the
*    operation was successful, FALSE if the stack_t was NULL or empty.
*  Parameters:
*    item ---> The item to add
*    stack ---> The stack_t to edit */
bool_t push(const T item, stack_t stack);

/* ---------------------------------------------------------------------
*  Pop
*  ---------------------------------------------------------------------
*  Description:
*    Removes the top element from the stack_t and assigns it to result,
*    then returns TRUE. If the stack_t is NULL or empty, it returns FALSE.
*  Parameters:
*    stack ---> The stack_t to edit 
*     result ---> Pointer to the result T value */
bool_t pop(stack_t stack, T* result);

/* ---------------------------------------------------------------------
*  Peek
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the top element without removing it from the stack_t.
*    Returns FALSE if the stack is NULL or empty.
*  Parameters:
*    stack ---> The input stack_t 
*    result ---> Pointer to the result T value */
bool_t peek(stack_t stack, T* result);

/* =====================================================================
*  LINQ
*  =====================================================================
*  Description:
*    LINQ-Style (.NET) functions that can be used to get informations 
*    from a list_t or to create new ones.
*  How-To:
*    Most of these functions take a pointer to function argument: it
*    is possible to create a standard function and pass a pointer to
*    it, or to create a lambda expression using the macro defined 
*    inside this header file.
*  NOTE:
*    All the functions inside this section are FUNCTIONAL and do NOT 
*    edit the input list_ts or their elements. */

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
*    returns a bool_t. Its body can be multiline as well.
*  Examples (assuming T is int):
*    selector(number, { return number > 10; })
*    selector(number,
*    {
*        if (number < 3) return (number * number) < 9;
*        else return !(number % 2);
*    }) */
#define selector(var_name, func_body) \
lambda(bool_t, (T var_name) func_body)

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
lambda(bool_t, (T var1_name, T var2_name) func_body)      \

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
*    Assigns to result the first element inside the list_t that
*    satisfies a given condition. It returns FALSE if the list_t was
*    NULL or empty, TRUE if the operation was successful.
*  Parameters:
*    list ---> The input list_t
*    result ---> Pointer to the result T value
*    expression ---> Selector lambda expression */
bool_t first_or_default(list_t list, T* result, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  LastOrDefault
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the last element inside the list_t that
*    satisfies a given condition. It returns FALSE if the list_t was
*    NULL or empty, TRUE if the operation was successful.
*  Parameters:
*    list ---> The input list_t
*    result ---> Pointer to the result T value
*    expression ---> Selector lambda expression */
bool_t last_or_default(list_t list, T* result, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  Count
*  ---------------------------------------------------------------------
*  Description:
*    Returns the number of elements inside the list_t that
*    satisfy the given expression.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Selector lambda expression */
int count(list_t list, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  FirstIndexWhere
*  ---------------------------------------------------------------------
*  Description:
*    Returns the index of the first item inside the list_t that satisfies
*    the given condition, or -1 if the list_t was NULL or if the item
*    was not present.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Selector lambda expression */
int first_index_where(list_t list, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  LastIndexWhere
*  ---------------------------------------------------------------------
*  Description:
*    Returns the index of the last item inside the list_t that satisfies
*    the given condition, or -1 if the list_t was NULL or if the item
*    was not present.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Selector lambda expression */
int last_index_where(list_t list, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  Where
*  ---------------------------------------------------------------------
*  Description:
*    Returns a list_t of all the elements inside the given
*    list that satisfy the given expression.
*    Returns NULL if the list_t was NULL.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Selector lambda expression */
list_t where(list_t list, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  TakeWhile
*  ---------------------------------------------------------------------
*  Description:
*    Keeps selecting items from the input list_t while the
*    current item satisfies the given expression, then returns the
*    new list_t. Returns NULL if the list_t was NULL.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Selector lambda expression */
list_t take_while(list_t list, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  TakeRange
*  ---------------------------------------------------------------------
*  Description:
*    Returns a list_t of all the items from the input list that
*    are located between the two given indexes, including them.
*    Returns NULL if the list_t was NULL or if the indexes were not valid.
*  Parameters:
*    list ---> The input list_t
*    start ---> The starting index
*    end ---> The final index (should be greater than the first one) */
list_t take_range(list_t list, int start, int end);

/* ---------------------------------------------------------------------
*  Concat
*  ---------------------------------------------------------------------
*  Description:
*    Creates a new list_t by adding all the items from the
*    second list_t to the items from the first list_t, and then returns it.
*    Returns NULL if either one of the two list_ts is NULL.
*  Parameters:
*    list1 ---> Its items will be the first ones in the new list_t
*    list2 ---> The second list_t to add at the end of the first one */
list_t concat(list_t list1, list_t list2);

/* ---------------------------------------------------------------------
*  Zip
*  ---------------------------------------------------------------------
*  Description:
*    Combines two list_ts using the given function to
*    create a new item from two different ones from the two list_ts.
*    Returns NULL if either one of the two list_ts is NULL or empty.
*    If the two list_ts have a different length, the new list_t will have
*    the same number of items of the longer list_t.
*  Parameters:
*    list1 ---> The first list_t to combine
*    list2 ---> Should have the same number of items of the first one
*    expression ---> Zipper lambda expression */
list_t zip(list_t list1, list_t list2, T(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Any
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE if at least one element inside the list
*    satisfies the given condition represented by the expression.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Selector lambda expression */
bool_t any(list_t list, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  All
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE only if all the items from the input
*    list satisfy the given condition.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Selector lambda expression */
bool_t all(list_t list, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  Skip
*  ---------------------------------------------------------------------
*  Description:
*    Skips the first n elements from the input list_t, then
*    creates a new list_t with the remaining elements and returns it.
*  Parameters:
*    list ---> The input list_t
*    count ---> The number of list_t items to skip */
list_t skip(list_t list, int count);

/* ---------------------------------------------------------------------
*  SkipWhile
*  ---------------------------------------------------------------------
*  Description:
*    Keeps skipping elements from the given list_t as long as they
*    satisfy the given condition, then returns the remaining items.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Selector lambda expression */
list_t skip_while(list_t list, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  ForEach
*  ---------------------------------------------------------------------
*  Description:
*    Executes the given function for each item of the given list_t.
*    Returns TRUE if the operation was successful, FALSE if the list_t
*    was either NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Block lambda expression */
bool_t for_each(list_t list, void(*expression)(T));

/* ---------------------------------------------------------------------
*  InverseForEach
*  ---------------------------------------------------------------------
*  Description:
*    Executes the given function for each item of the given list_t,
*    starting from the last one and moving backwards.
*    Returns TRUE if the operation was successful, FALSE if the list_t
*    was either NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Block lambda expression */
bool_t inverse_for_each(list_t list, void(*expression)(T));

/* ---------------------------------------------------------------------
*  Join
*  ---------------------------------------------------------------------
*  Description:
*    Performs the union operation between two list_ts. Returns NULL
*    if either one of the two list_ts is NULL.
*  Parameters:
*    list1 ---> The first input list_t
*    list2 ---> The second list_t, it can have an arbitrary length
*    expression ---> EqualityTester lambda expression */
list_t join(list_t list1, list_t list2, bool_t(*expression)(T, T));

/* ---------------------------------------------------------------------
*  JoinWhere
*  ---------------------------------------------------------------------
*  Description:
*    Selects all the items inside the two list_ts that satisfy the given
*    condition and then performs the union operation between these two
*    sub list_ts. Returns NULL if either one of the two list_ts is NULL.
*  Parameters:
*    list1 ---> The first input list_t
*    list2 ---> The second list_t, it can have an arbitrary length
*    condition ---> Selector lambda expression
*    expression ---> EqualityTester lambda expression */
list_t join_where(list_t list1, list_t list2, bool_t(*condition)(T), bool_t(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Intersect
*  ---------------------------------------------------------------------
*  Description:
*    Performs the intersection between two list_ts. Returns NULL
*    if either one of the two list_ts is NULL.
*  Parameters:
*    list1 ---> The first input list_t
*    list2 ---> The second list_t, it can have an arbitrary length
*    expression ---> EqualityTester lambda expression */
list_t intersect(list_t list1, list_t list2, bool_t(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Except
*  ---------------------------------------------------------------------
*  Description:
*    Performs the subtraction operation between two list_ts.
*    i.e: it returns a new list_t that contains all the elements that
*    were present inside the first list_t and not in the second one.
*    Returns NULL if either one of the two list_ts is NULL.
*  Parameters:
*    list1 ---> The first input list_t
*    list2 ---> The second list_t, it can have an arbitrary length
*    expression ---> EqualityTester lambda expression */
list_t except(list_t list1, list_t list2, bool_t(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Reverse
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list_t that contains all the elements from
*    the given list_t, but added in reverse order.
*    Returns NULL if the list_t is NULL or empty.
*  Parameters:
*    list ---> The input list_t */
list_t reverse(list_t list);

/* ---------------------------------------------------------------------
*  ReverseRange
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list_t that contains all the items from the source list_t,
*    with a reversed order for the ones that included inside the
*    given range. Returns NULL if the list_t is NULL or empty or
*    if the indexes are not valid.
*  Parameters:
*    list ---> The input list_t
*    start ---> The start index for the reversed section
*    end ---> The index of the last element with the reversed order */
list_t reverse_range(list_t list, int start, int end);

/* ---------------------------------------------------------------------
*  Sum
*  ---------------------------------------------------------------------
*  Description:
*    Calculates the sum of all the items inside the list_t using
*    the given function to get a numeric number from each item.
*    Returns (T)NULL if the list is NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> ToNumber lambda expression */
int sum(list_t list, int(*expression)(T));

/* ---------------------------------------------------------------------
*  Average
*  ---------------------------------------------------------------------
*  Description:
*    Calculates the average between all the items inside the
*    list_t using the given function to get a numeric number from each
*    item. Returns (T)NULL if the list is NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> ToNumber lambda expression */
int average(list_t list, int(*expression)(T));

/* ---------------------------------------------------------------------
*  GetNumericMin
*  ---------------------------------------------------------------------
*  Description:
*    Returns the minimum integer value from the list using
*    the given function to convert each item to a numeric value.
*    Returns (T)NULL if the list is NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> ToNumber lambda expression */
int get_numeric_min(list_t list, int(*expression)(T));

/* ---------------------------------------------------------------------
*  GetMin
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the item with the lower value, using the given
*    function to compare the elements of the list_t.
*    Returns FALSE if the list_t was NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    result ---> Pointer to the result T value
*    expression ---> Comparator lambda expression */
bool_t get_min(list_t list, T* result, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  GetNumericMax
*  ---------------------------------------------------------------------
*  Description:
*    Returns the maximum integer value from the list using
*    the given function to convert each item to a numeric value.
*    Returns (T)NULL if the list is NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> ToNumber lambda expression */
int get_numeric_max(list_t list, int(*expression)(T));

/* ---------------------------------------------------------------------
*  GetMax
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the item with the higher value, using the given
*    function to compare the elements of the list_t.
*    Returns FALSE if the list_t was NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    result ---> Pointer to the result T value
*    expression ---> Comparator lambda expression */
bool_t get_max(list_t list, T* result, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  OrderBy
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list_t with all the elements from the input list_t,
*    ordered using the given expression.
*    This function uses additional memory to speed up the sorting
*    operation and uses the introsort algorithm, which has a worst
*    case cost of O(nlogn). Returns NULL if the list_t is NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Comparator lambda expression */
list_t order_by(list_t list, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  OrderByDescending
*  ---------------------------------------------------------------------
*  Description:
*    Calls the OrderBy function and returns it in reverse order.
*    The worst case cost is the same: O(nlogn).
*  Parameters:
*    list ---> The input list_t
*    expression ---> Comparator lambda expression */
list_t order_by_descending(list_t list, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  InPlaceOrderBy
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list_t with all the elements from the input list_t,
*    ordered using the given expression.
*    This function uses the Bubble Sort algorithm: O(n^2).
*    Returns NULL if the list_t is NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Comparator lambda expression */
list_t in_place_order_by(list_t list, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  InPlaceOrderByDescending
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list_t with all the elements from the input list_t,
*    ordered using the given expression and in reversed order.
*    This function uses the Sort algorithm: O(n^2).
*    Returns NULL if the list_t is NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Comparator lambda expression */
list_t in_place_order_by_descending(list_t list, comparation(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Distinct
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list_t that contains all the single elements
*    from the input list_t, using the given expression to compare the
*    items. Returns NULL if the list_t is NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> EqualityTester lambda expression */
list_t distinct(list_t list, bool_t(*expression)(T, T));

/* ---------------------------------------------------------------------
*  CountDistinct
*  ---------------------------------------------------------------------
*  Description:
*    Returns the number of distinct elements inside the given list_t.
*    If the list_t is NULL, the function returns -1.
*  Parameters:
*    list ---> The input list_t
*    expression ---> EqualityTester lambda expression */
int count_distinct(list_t list, bool_t(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Single
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the single element inside the list_t that 
*    satisfies the given condition. If there is more than an item, 
*    if the list_t is NULL or empty, or if the list doesn't contain
*    an item that satisfies the condition, the function returns FALSE.
*  Parameters:
*    list ---> The input list_t
*    result ---> Pointer to the result T value
*    expression ---> Selector lambda expression */
bool_t single(list_t list, T* result, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  RemoveWhere
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list_t with all the elements from the given
*    list_t except for those that satisfy the current expression.
*    Returns NULL if the list_t is either NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Selector lambda expression */
list_t remove_where(list_t list, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  ReplaceWhere
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list_t where all the items that satisfied the
*    expression were replaced with the given constant value.
*    Returns NULL if the list_t is either NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    replacement ---> The value to use when replacing an item
*    expression ---> Selector lambda expression */
list_t replace_where(list_t list, const T replacement, bool_t(*expression)(T));

/* ---------------------------------------------------------------------
*  Derive
*  ---------------------------------------------------------------------
*  Description:
*    Derives a new list_t applying the given expression to each element.
*    Returns NULL if the list_t is either NULL or empty.
*  Parameters:
*    list ---> The input list_t
*    expression ---> Deriver lambda expression */
list_t derive(list_t list, T(*expression)(T));

/* ---------------------------------------------------------------------
*  SequenceEquals
*  ---------------------------------------------------------------------
*  Description:
*    Returns TRUE if two list_ts have the same length and their elements
*    are equals and in the same order, FALSE otherwise.
*    If both the list_ts are NULL, the function returns TRUE.
*  Parameters:
*    list1 ---> The input list_t
*    list2 ---> Should have the same length as the first one
*    expression ---> EqualityTester lambda expression */
bool_t sequence_equals(list_t list1, list_t list2, bool_t(*expression)(T, T));

/* ---------------------------------------------------------------------
*  Trim
*  ---------------------------------------------------------------------
*  Description:
*    Returns a new list with all the elements from the first one, and
*    the maximum length adjusted to the given number.
*    Returns NULL if the list_t is either NULL or empty.
*  Parameters:
*    list ---> The source list_t
*    length ---> The maximum length for the new list_t */
list_t trim(list_t list, int length);

/* =====================================================================
*  Iterator
*  =====================================================================
*  Description:
*    Functions that create and manage list_t Iterators.
*  NOTE:
*    Each list_t can have multiple Iterators, as they are completely
*    indipendent from their original list_t. Each Iterator is synced with
*    the original state of the list_t it is referring to: if the 
*    collection is modified the Iterator will become invalid and it will
*    be necessary to restart it. As in foreach loops in other
*    languages, this is done in order to prevent unwanted side effects
*    when using the Iterator. */

/* ---------------------------------------------------------------------
*  GetIterator
*  ---------------------------------------------------------------------
*  Description:
*    Creates and returns a new Iterator for the given list_t. Returns
*    NULL if the list_t is NULL or empty.
*  Parameters:
*    list ---> The source list_t */
list_iterator_t get_iterator(list_t list);

/* ---------------------------------------------------------------------
*  DestroyIterator
*  ---------------------------------------------------------------------
*  Description:
*    Deallocates an Iterator and sets it to NULL. It returns True if
*    the operation was successful, FALSE if the iterator was NULL.
*  Parameters:
*    iterator ---> A pointer to the target iterator */
bool_t destroy_iterator(list_iterator_t* iterator);

/* ---------------------------------------------------------------------
*  IsSynced
*  ---------------------------------------------------------------------
*  Description:
*    Checks if the target list_t has been edited after the Iterator
*    was created. Returns FALSE if the Iterator is NULL or out of sync,
*    TRUE otherwise.
*  Parameters:
*    iterator ---> The input Iterator */
bool_t is_synced(list_iterator_t iterator);

/* ---------------------------------------------------------------------
*  GetCurrent
*  ---------------------------------------------------------------------
*  Description:
*    Assigns to result the current item pointed by the Iterator. If the 
*    iterator is NULL or out of sync, the function returns FALSE.
*  Parameters:
*    iterator ---> The input iterator 
*    result ---> Pointer to the result T value */
bool_t get_current(list_iterator_t iterator, T* result);

/* ---------------------------------------------------------------------
*  Next
*  ---------------------------------------------------------------------
*  Description:
*    Functions that emulates the standard behaviour of an Iterator in
*    an Object Oriented Language. The first time this function is
*    called, it assigns to result the first element inside the list_t, 
*    then keeps moving next and assigns the following item each time.
*    If the Iterator is NULL, out of sync, or if there isn't
*    another item left inside the list_t, the function returns FALSE.
*  NOTE:
*    This function will ONLY start from the first element if the
*    position of the Iterator has never been changed since its
*    creation. Otherwise it starts returning items from its actual 
*    position inside the target list_t.
*  Parameters:
*    iterator ---> The input iterator
*    result ---> Pointer to the result T value */
bool_t next(list_iterator_t iterator, T* result);

/* ---------------------------------------------------------------------
*  CanGoForward
*  ---------------------------------------------------------------------
*  Description:
*    Checks if the Iterator can move forward. It returns FALSE if the
*    iterator is NULL, out of sync, or if there isn't another item left
*    inside the target list_t, TRUE otherwise.
*  Parameters:
*    iterator ---> The input iterator */
bool_t can_go_forward(list_iterator_t iterator);

/* ---------------------------------------------------------------------
*  CanGoBack
*  ---------------------------------------------------------------------
*  Description:
*    Checks if the Iterator can move back. It returns FALSE if the
*    iterator is NULL, out of sync, or if it already points to the 
*    first element of the target list_t, TRUE otherwise.
*  Parameters:
*    iterator ---> The input iterator */
bool_t can_go_back(list_iterator_t iterator);

/* ---------------------------------------------------------------------
*  MoveNext
*  ---------------------------------------------------------------------
*  Description:
*    Moves the Iterator to its next list_t element, and returns TRUE
*    if the Iterator was not NULL and the operation was successful.
*  Parameters:
*    iterator ---> The input iterator */
bool_t move_next(list_iterator_t iterator);

/* ---------------------------------------------------------------------
*  MoveBack
*  ---------------------------------------------------------------------
*  Description:
*    Moves the Iterator to its previous list_t element, and returns TRUE
*    if the Iterator was not NULL and the operation was successful.
*  Parameters:
*    iterator ---> The input iterator */
bool_t move_back(list_iterator_t iterator);

/* ---------------------------------------------------------------------
*  ActualPosition
*  ---------------------------------------------------------------------
*  Description:
*    Returns the current position of the Iterator inside its target list_t.
*    If the Iterator is NULL or out of sync the function returns -1.
*  Parameters:
*    iterator ---> The input iterator */
int actual_position(list_iterator_t iterator);

/* ---------------------------------------------------------------------
*  ElementsLeft
*  ---------------------------------------------------------------------
*  Description:
*    Calculates the number of elements inside the list, starting from
*    the actual position of the Iterator. 
*    Returns -1 if it is NULL or out of sync.
*  Parameters:
*    iterator ---> The input iterator */
int elements_left(list_iterator_t iterator);

/* ---------------------------------------------------------------------
*  ForEachRemaining
*  ---------------------------------------------------------------------
*  Description:
*    Moves the Iterator forward until it reaches the last item inside
*    the list_t, and performs the given code block for each element.
*    If the operation was successful, it returns the number of times
*    the given expression was executed, otherwise it returns -1.
*  Parameters:
*    iterator ---> The input iterator
*    expression ---> Block lambda expression */
int for_each_remaining(list_iterator_t iterator, void(*expression)(T));

/* ---------------------------------------------------------------------
*  Restart
*  ---------------------------------------------------------------------
*  Description:
*    Moves the Iterator back to the first position of its target list_t.
*    It also makes sure the Iterator is synced with the list_t.
*  Parameters:
*    iterator ---> The input iterator */
bool_t restart(list_iterator_t iterator);

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