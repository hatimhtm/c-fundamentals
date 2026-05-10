/**
 * @file quicksort.c
 * @brief Quicksort using Lomuto partition.
 *
 * Average O(n log n), worst O(n²) on already-sorted input. Tail-recursion
 * on the smaller partition would bound the stack depth at O(log n) — kept
 * straightforward here for readability.
 */

#include "sorts.h"
#include <string.h>

/* ── String variant ─────────────────────────────────────────────────── */

static void swap_str(char **a, char **b) {
  char *t = *a;
  *a = *b;
  *b = t;
}

static long lomuto_partition_str(char **arr, long lo, long hi) {
  char *pivot = arr[hi];
  long i = lo - 1;
  for (long j = lo; j < hi; j++) {
    if (strcmp(arr[j], pivot) <= 0) {
      i++;
      swap_str(&arr[i], &arr[j]);
    }
  }
  swap_str(&arr[i + 1], &arr[hi]);
  return i + 1;
}

static void quicksort_str_recursive(char **arr, long lo, long hi) {
  if (lo < hi) {
    long p = lomuto_partition_str(arr, lo, hi);
    quicksort_str_recursive(arr, lo, p - 1);
    quicksort_str_recursive(arr, p + 1, hi);
  }
}

void quicksort_strings(char **arr, size_t n) {
  if (n <= 1) return;
  quicksort_str_recursive(arr, 0, (long)n - 1);
}

/* ── Integer variant ────────────────────────────────────────────────── */

static void swap_int(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

static long lomuto_partition_int(int *arr, long lo, long hi) {
  int pivot = arr[hi];
  long i = lo - 1;
  for (long j = lo; j < hi; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap_int(&arr[i], &arr[j]);
    }
  }
  swap_int(&arr[i + 1], &arr[hi]);
  return i + 1;
}

static void quicksort_int_recursive(int *arr, long lo, long hi) {
  if (lo < hi) {
    long p = lomuto_partition_int(arr, lo, hi);
    quicksort_int_recursive(arr, lo, p - 1);
    quicksort_int_recursive(arr, p + 1, hi);
  }
}

void quicksort_ints(int *arr, size_t n) {
  if (n <= 1) return;
  quicksort_int_recursive(arr, 0, (long)n - 1);
}
