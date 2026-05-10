/**
 * @file binary_search.c
 * @brief Iterative + recursive binary search.
 *
 * Note the `lo + (hi - lo) / 2` midpoint computation — `(lo + hi) / 2`
 * would overflow on huge arrays. With size_t we'd need n > SIZE_MAX/2 to
 * actually trip it, but the safer form is free.
 */

#include "binary_search.h"
#include <string.h>

size_t binary_search_ints(const int *arr, size_t n, int target) {
  if (n == 0) return BSEARCH_NOT_FOUND;
  size_t lo = 0, hi = n - 1;
  while (lo <= hi) {
    size_t mid = lo + (hi - lo) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) {
      lo = mid + 1;
    } else {
      if (mid == 0) break; /* avoid underflow on size_t */
      hi = mid - 1;
    }
  }
  return BSEARCH_NOT_FOUND;
}

size_t binary_search_strings(const char *const *arr, size_t n, const char *target) {
  if (n == 0 || target == NULL) return BSEARCH_NOT_FOUND;
  size_t lo = 0, hi = n - 1;
  while (lo <= hi) {
    size_t mid = lo + (hi - lo) / 2;
    int cmp = strcmp(arr[mid], target);
    if (cmp == 0) return mid;
    if (cmp < 0) {
      lo = mid + 1;
    } else {
      if (mid == 0) break;
      hi = mid - 1;
    }
  }
  return BSEARCH_NOT_FOUND;
}

size_t binary_search_ints_recursive(const int *arr, size_t lo, size_t hi, int target) {
  if (lo > hi) return BSEARCH_NOT_FOUND;
  size_t mid = lo + (hi - lo) / 2;
  if (arr[mid] == target) return mid;
  if (arr[mid] < target) return binary_search_ints_recursive(arr, mid + 1, hi, target);
  if (mid == 0) return BSEARCH_NOT_FOUND;
  return binary_search_ints_recursive(arr, lo, mid - 1, target);
}
