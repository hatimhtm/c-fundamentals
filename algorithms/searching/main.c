/**
 * @file main.c
 * @brief Binary search CLI demo.
 *
 * Usage:
 *   bsearch <target> <num1> <num2> ...
 *
 * The trailing numbers are sorted internally (insertion sort, since the
 * input list is small) before the search runs.
 */

#include "../sorting/sorts.h"
#include "binary_search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_array(const int *arr, size_t n) {
  printf("[");
  for (size_t i = 0; i < n; i++) {
    printf("%d", arr[i]);
    if (i + 1 < n) printf(", ");
  }
  printf("]");
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <target> <num1> <num2> ...\n", argv[0]);
    printf("\nExample: %s 7 3 1 9 7 4 2\n", argv[0]);
    return EXIT_FAILURE;
  }

  int target = atoi(argv[1]);
  size_t n = (size_t)(argc - 2);
  int *arr = malloc(n * sizeof(int));
  if (!arr) return EXIT_FAILURE;

  for (size_t i = 0; i < n; i++) arr[i] = atoi(argv[i + 2]);

  insertion_sort_ints(arr, n);

  printf("Sorted: ");
  print_array(arr, n);
  printf("\nTarget: %d\n", target);

  size_t idx = binary_search_ints(arr, n, target);
  if (idx == BSEARCH_NOT_FOUND) {
    printf("Result: not found\n");
  } else {
    printf("Result: found at index %zu\n", idx);
  }

  free(arr);
  return EXIT_SUCCESS;
}
