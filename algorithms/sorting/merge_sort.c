/**
 * @file merge_sort.c
 * @brief Top-down merge sort with explicit auxiliary buffer.
 *
 * Stable, O(n log n) worst-case, O(n) extra space. The aux buffer is
 * allocated once at the top-level call and reused for every merge to
 * avoid per-recursion malloc churn.
 */

#include "sorts.h"
#include <stdlib.h>
#include <string.h>

/* ── String variant ─────────────────────────────────────────────────── */

static void merge_str(char **arr, char **aux, size_t lo, size_t mid, size_t hi) {
  for (size_t k = lo; k <= hi; k++) aux[k] = arr[k];

  size_t i = lo, j = mid + 1, k = lo;
  while (i <= mid && j <= hi) {
    if (strcmp(aux[i], aux[j]) <= 0) arr[k++] = aux[i++];
    else                              arr[k++] = aux[j++];
  }
  while (i <= mid) arr[k++] = aux[i++];
  while (j <= hi)  arr[k++] = aux[j++];
}

static void merge_sort_str_recursive(char **arr, char **aux, size_t lo, size_t hi) {
  if (lo >= hi) return;
  size_t mid = lo + (hi - lo) / 2;
  merge_sort_str_recursive(arr, aux, lo, mid);
  merge_sort_str_recursive(arr, aux, mid + 1, hi);
  merge_str(arr, aux, lo, mid, hi);
}

void merge_sort_strings(char **arr, size_t n) {
  if (n <= 1) return;
  char **aux = malloc(n * sizeof(char *));
  if (!aux) return; /* Graceful degradation — array stays unsorted. */
  merge_sort_str_recursive(arr, aux, 0, n - 1);
  free(aux);
}

/* ── Integer variant ────────────────────────────────────────────────── */

static void merge_int(int *arr, int *aux, size_t lo, size_t mid, size_t hi) {
  for (size_t k = lo; k <= hi; k++) aux[k] = arr[k];

  size_t i = lo, j = mid + 1, k = lo;
  while (i <= mid && j <= hi) {
    if (aux[i] <= aux[j]) arr[k++] = aux[i++];
    else                  arr[k++] = aux[j++];
  }
  while (i <= mid) arr[k++] = aux[i++];
  while (j <= hi)  arr[k++] = aux[j++];
}

static void merge_sort_int_recursive(int *arr, int *aux, size_t lo, size_t hi) {
  if (lo >= hi) return;
  size_t mid = lo + (hi - lo) / 2;
  merge_sort_int_recursive(arr, aux, lo, mid);
  merge_sort_int_recursive(arr, aux, mid + 1, hi);
  merge_int(arr, aux, lo, mid, hi);
}

void merge_sort_ints(int *arr, size_t n) {
  if (n <= 1) return;
  int *aux = malloc(n * sizeof(int));
  if (!aux) return;
  merge_sort_int_recursive(arr, aux, 0, n - 1);
  free(aux);
}
