/**
 * @file binary_search.h
 * @brief Binary search on sorted arrays. O(log n) time, O(1) space.
 *
 * Returns the index of the target if found, or `(size_t)-1` if not.
 * The input array MUST be sorted in ascending order — the caller's
 * responsibility, not checked here.
 */

#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <stddef.h>

#define BSEARCH_NOT_FOUND ((size_t)-1)

size_t binary_search_ints(const int *arr, size_t n, int target);
size_t binary_search_strings(const char *const *arr, size_t n, const char *target);

/* Recursive variant for the curious — same complexity, used in tests. */
size_t binary_search_ints_recursive(const int *arr, size_t lo, size_t hi, int target);

#endif /* BINARY_SEARCH_H */
