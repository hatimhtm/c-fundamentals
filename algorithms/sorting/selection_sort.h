/**
 * @file selection_sort.h
 * @brief Selection sort algorithm for string arrays
 * 
 * This module provides functions to sort arrays of strings using
 * the selection sort algorithm. Selection sort has O(n²) time complexity
 * but is simple to understand and implement.
 */

#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <stddef.h>

/**
 * @brief Sort an array of strings alphabetically using selection sort
 * 
 * @param arr Array of string pointers to sort
 * @param n Number of elements in the array
 * 
 * @note The array is sorted in-place
 * @note Time complexity: O(n²)
 * @note Space complexity: O(1)
 */
void selection_sort_strings(char **arr, size_t n);

/**
 * @brief Sort an array of integers using selection sort
 * 
 * @param arr Array of integers to sort
 * @param n Number of elements in the array
 */
void selection_sort_ints(int *arr, size_t n);

/**
 * @brief Find the index of the minimum element in a range
 * 
 * @param arr Array of strings
 * @param start Starting index
 * @param n Total number of elements
 * @return Index of the minimum element
 */
size_t find_min_index(char **arr, size_t start, size_t n);

#endif /* SELECTION_SORT_H */
