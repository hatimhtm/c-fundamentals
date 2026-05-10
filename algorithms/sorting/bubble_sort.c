/**
 * @file bubble_sort.c
 * @brief Bubble sort with early-exit optimization.
 *
 * Repeatedly walk the array, swapping adjacent out-of-order pairs.
 * If a full pass produced no swaps the array is sorted — bail early.
 * Stable, O(n²) worst, O(n) best.
 */

#include "sorts.h"
#include <stdbool.h>
#include <string.h>

void bubble_sort_strings(char **arr, size_t n) {
  if (n <= 1) return;
  for (size_t i = 0; i < n - 1; i++) {
    bool swapped = false;
    for (size_t j = 0; j < n - 1 - i; j++) {
      if (strcmp(arr[j], arr[j + 1]) > 0) {
        char *tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
        swapped = true;
      }
    }
    if (!swapped) return;
  }
}

void bubble_sort_ints(int *arr, size_t n) {
  if (n <= 1) return;
  for (size_t i = 0; i < n - 1; i++) {
    bool swapped = false;
    for (size_t j = 0; j < n - 1 - i; j++) {
      if (arr[j] > arr[j + 1]) {
        int tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
        swapped = true;
      }
    }
    if (!swapped) return;
  }
}
