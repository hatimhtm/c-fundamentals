/**
 * @file benchmark.c
 * @brief Empirical comparison of all five sort algorithms.
 *
 * For each of {100, 1000, 10000} random integers, run each sort against
 * the same input and report wall-clock time in milliseconds. Output is
 * a Markdown table so it can be pasted straight into READMEs.
 */

#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef void (*sort_fn)(int *, size_t);

typedef struct {
  const char *name;
  sort_fn fn;
} sort_entry_t;

static const sort_entry_t SORTS[] = {
  {"Selection", selection_sort_ints},
  {"Bubble",    bubble_sort_ints},
  {"Insertion", insertion_sort_ints},
  {"Quicksort", quicksort_ints},
  {"Merge",     merge_sort_ints},
};
static const size_t N_SORTS = sizeof(SORTS) / sizeof(SORTS[0]);

static const size_t SIZES[] = {100, 1000, 10000};
static const size_t N_SIZES = sizeof(SIZES) / sizeof(SIZES[0]);

/** Fills `out` with `n` deterministically-shuffled integers in [0, n). */
static void fill_random(int *out, size_t n, unsigned seed) {
  srand(seed);
  for (size_t i = 0; i < n; i++) out[i] = (int)(rand() % (int)n);
}

static double time_sort_ms(sort_fn fn, int *arr, size_t n) {
  struct timespec t0, t1;
  clock_gettime(CLOCK_MONOTONIC, &t0);
  fn(arr, n);
  clock_gettime(CLOCK_MONOTONIC, &t1);
  return (t1.tv_sec - t0.tv_sec) * 1000.0
       + (t1.tv_nsec - t0.tv_nsec) / 1e6;
}

int main(void) {
  printf("# Sort benchmarks (random integers)\n\n");
  printf("| Algorithm  ");
  for (size_t s = 0; s < N_SIZES; s++) printf("| n=%-6zu ", SIZES[s]);
  printf("|\n|------------");
  for (size_t s = 0; s < N_SIZES; s++) printf("|---------");
  printf("|\n");

  /* Allocate the largest buffer once. */
  size_t max_n = SIZES[N_SIZES - 1];
  int *original = malloc(max_n * sizeof(int));
  int *working = malloc(max_n * sizeof(int));
  if (!original || !working) {
    fprintf(stderr, "out of memory\n");
    free(original); free(working);
    return EXIT_FAILURE;
  }

  for (size_t i = 0; i < N_SORTS; i++) {
    printf("| %-10s ", SORTS[i].name);
    for (size_t s = 0; s < N_SIZES; s++) {
      size_t n = SIZES[s];
      fill_random(original, n, 42 /* deterministic */);
      memcpy(working, original, n * sizeof(int));
      double ms = time_sort_ms(SORTS[i].fn, working, n);
      printf("| %7.2fms ", ms);
    }
    printf("|\n");
  }

  free(original);
  free(working);
  return EXIT_SUCCESS;
}
