/**
 * @file selection_sort.c
 * @brief Implementation of selection sort algorithm
 *
 * Selection sort works by repeatedly finding the minimum element
 * from the unsorted portion and placing it at the beginning.
 */

#include "sorts.h"
#include <string.h>

size_t find_min_index(char **arr, size_t start, size_t n) {
  size_t min_idx = start;

  for (size_t j = start + 1; j < n; j++) {
    if (strcmp(arr[j], arr[min_idx]) < 0) {
      min_idx = j;
    }
  }

  return min_idx;
}

void selection_sort_strings(char **arr, size_t n) {
  if (n <= 1)
    return;

  for (size_t i = 0; i < n - 1; i++) {
    // Find the minimum element in unsorted portion
    size_t min_idx = find_min_index(arr, i, n);

    // Swap with the first unsorted element
    if (min_idx != i) {
      char *temp = arr[i];
      arr[i] = arr[min_idx];
      arr[min_idx] = temp;
    }
  }
}

void selection_sort_ints(int *arr, size_t n) {
  if (n <= 1)
    return;

  for (size_t i = 0; i < n - 1; i++) {
    size_t min_idx = i;

    for (size_t j = i + 1; j < n; j++) {
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }

    if (min_idx != i) {
      int temp = arr[i];
      arr[i] = arr[min_idx];
      arr[min_idx] = temp;
    }
  }
}
