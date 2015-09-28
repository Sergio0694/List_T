#ifndef INTROSORT_H
#define INTROSORT_H

/* ---------------------------------------------------------------------
*  Introsort
*  ---------------------------------------------------------------------
*  Description:
*    Sorts a target vector using a custom introsort algorithm that
*    combines the classic introsort with an insertion sort when the
*    sub-array to sort is small enough. This algorithm has a worst case
*    cost of O(nlogn) and it is faster than the heapsort algorithm,
*    while using less memory than a quicksort algorithm.
*  Parameters:
*    vector ---> The vector to sort
*    len ---> The number of elements in the vector to sort
*    expression ---> Comparator lambda expression (see the list_t.h file) */
void introsort(T* vector, int len, comparation(*expression)(T, T));

#endif