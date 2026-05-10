/**
 * @file radix_sort.c
 * @brief LSD radix sort for non-negative ints, byte-by-byte.
 *
 * Uses 4 passes (one per byte of a 32-bit int) of stable counting sort.
 * Linear in n × bytes — i.e. effectively O(n) when the value range is
 * bounded. Operates on `unsigned int` internally to keep the byte
 * extraction unambiguous; assumes input is non-negative.
 *
 * Returns silently without sorting if any value is negative — this is a
 * teaching implementation, not a general-purpose replacement for quicksort.
 */

#include "sorts.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define RADIX_BUCKETS 256

static void counting_pass(uint32_t *src, uint32_t *dst, size_t n, int byte_idx) {
  size_t count[RADIX_BUCKETS] = {0};

  for (size_t i = 0; i < n; i++) {
    unsigned b = (unsigned)((src[i] >> (byte_idx * 8)) & 0xFF);
    count[b]++;
  }
  for (int i = 1; i < RADIX_BUCKETS; i++) count[i] += count[i - 1];

  /* Stable: walk source in reverse so equal keys preserve their order. */
  for (size_t i = n; i > 0; i--) {
    uint32_t v = src[i - 1];
    unsigned b = (unsigned)((v >> (byte_idx * 8)) & 0xFF);
    dst[--count[b]] = v;
  }
}

void radix_sort_ints(int *arr, size_t n) {
  if (n <= 1) return;

  /* Reject negatives — this implementation is unsigned-only. */
  for (size_t i = 0; i < n; i++) {
    if (arr[i] < 0) return;
  }

  uint32_t *buf_a = malloc(n * sizeof(uint32_t));
  uint32_t *buf_b = malloc(n * sizeof(uint32_t));
  if (!buf_a || !buf_b) { free(buf_a); free(buf_b); return; }

  for (size_t i = 0; i < n; i++) buf_a[i] = (uint32_t)arr[i];

  counting_pass(buf_a, buf_b, n, 0);
  counting_pass(buf_b, buf_a, n, 1);
  counting_pass(buf_a, buf_b, n, 2);
  counting_pass(buf_b, buf_a, n, 3);

  for (size_t i = 0; i < n; i++) arr[i] = (int)buf_a[i];

  free(buf_a);
  free(buf_b);
}
