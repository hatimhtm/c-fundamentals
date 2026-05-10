/**
 * @file heap_sort.c
 * @brief In-place heap sort. O(n log n) worst case, O(1) auxiliary memory.
 *
 * Step 1: build a max-heap in place from the input (linear time via
 *         Floyd's bottom-up sift-down).
 * Step 2: repeatedly swap arr[0] (max) with arr[end] and sift-down the
 *         shrinking heap; the sorted suffix grows from the right.
 *
 * Re-uses heap_sift_down_max from data_structures/heap.
 */

#include "../../data_structures/heap/heap.h"
#include "sorts.h"

void heap_sort_ints(int *arr, size_t n) {
  if (n <= 1) return;

  /* Build max-heap. */
  for (size_t i = n / 2; i > 0; i--) {
    heap_sift_down_max(arr, i - 1, n);
  }

  /* Extract elements one by one — sorted suffix grows from arr[n-1] leftward. */
  for (size_t end = n - 1; end > 0; end--) {
    int tmp = arr[0]; arr[0] = arr[end]; arr[end] = tmp;
    heap_sift_down_max(arr, 0, end);
  }
}

/* ── String variant: max-heap on strcmp comparisons ─────────────────── */

#include <string.h>

static void sift_down_max_str(char **arr, size_t i, size_t n) {
  while (1) {
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t largest = i;
    if (left  < n && strcmp(arr[left],  arr[largest]) > 0) largest = left;
    if (right < n && strcmp(arr[right], arr[largest]) > 0) largest = right;
    if (largest == i) break;
    char *tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
    i = largest;
  }
}

void heap_sort_strings(char **arr, size_t n) {
  if (n <= 1) return;
  for (size_t i = n / 2; i > 0; i--) sift_down_max_str(arr, i - 1, n);
  for (size_t end = n - 1; end > 0; end--) {
    char *tmp = arr[0]; arr[0] = arr[end]; arr[end] = tmp;
    sift_down_max_str(arr, 0, end);
  }
}
