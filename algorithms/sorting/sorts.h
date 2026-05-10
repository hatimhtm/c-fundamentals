/**
 * @file sorts.h
 * @brief Unified header for all sorting algorithms.
 *
 * Each algorithm has both a string and an int variant so the same
 * benchmark harness can compare them on a uniform input type.
 *
 * | Algorithm      | Time (avg)  | Time (worst) | Space   | Stable |
 * |----------------|-------------|--------------|---------|--------|
 * | Selection sort | O(n²)       | O(n²)        | O(1)    | No     |
 * | Bubble sort    | O(n²)       | O(n²)        | O(1)    | Yes    |
 * | Insertion sort | O(n²)       | O(n²)        | O(1)    | Yes    |
 * | Quicksort      | O(n log n)  | O(n²)        | O(log n)| No     |
 * | Merge sort     | O(n log n)  | O(n log n)   | O(n)    | Yes    |
 */

#ifndef SORTS_H
#define SORTS_H

#include <stddef.h>

/* ── Selection sort ─────────────────────────────────────────────────── */
void selection_sort_strings(char **arr, size_t n);
void selection_sort_ints(int *arr, size_t n);
size_t find_min_index(char **arr, size_t start, size_t n);

/* ── Insertion sort ─────────────────────────────────────────────────── */
void insertion_sort_strings(char **arr, size_t n);
void insertion_sort_ints(int *arr, size_t n);

/* ── Bubble sort ────────────────────────────────────────────────────── */
void bubble_sort_strings(char **arr, size_t n);
void bubble_sort_ints(int *arr, size_t n);

/* ── Quicksort (Lomuto partition) ───────────────────────────────────── */
void quicksort_strings(char **arr, size_t n);
void quicksort_ints(int *arr, size_t n);

/* ── Merge sort ─────────────────────────────────────────────────────── */
void merge_sort_strings(char **arr, size_t n);
void merge_sort_ints(int *arr, size_t n);

#endif /* SORTS_H */
