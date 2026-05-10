/**
 * @file insertion_sort.c
 * @brief Insertion sort — stable, O(n²) worst, O(n) on nearly-sorted input.
 *
 * Walk the array left-to-right; for each element, slide it leftward over
 * any larger predecessors until it lands in its sorted slot.
 */

#include "sorts.h"
#include <string.h>

void insertion_sort_strings(char **arr, size_t n) {
  if (n <= 1) return;
  for (size_t i = 1; i < n; i++) {
    char *key = arr[i];
    size_t j = i;
    while (j > 0 && strcmp(arr[j - 1], key) > 0) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = key;
  }
}

void insertion_sort_ints(int *arr, size_t n) {
  if (n <= 1) return;
  for (size_t i = 1; i < n; i++) {
    int key = arr[i];
    size_t j = i;
    while (j > 0 && arr[j - 1] > key) {
      arr[j] = arr[j - 1];
      j--;
    }
    arr[j] = key;
  }
}
