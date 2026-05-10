/**
 * @file heap.h
 * @brief Binary min-heap (array-backed priority queue) of `int`.
 *
 * Min-heap: parent ≤ children. Array layout — for index `i`,
 * left child = 2i+1, right child = 2i+2, parent = (i-1)/2.
 *
 * | Operation     | Time     |
 * |---------------|----------|
 * | insert        | O(log n) |
 * | extract_min   | O(log n) |
 * | peek_min      | O(1)     |
 * | heapify (build from array) | O(n) — linear via sift-down |
 */

#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stddef.h>

typedef struct heap heap_t;

heap_t *heap_create(void);
void heap_destroy(heap_t *h);

bool heap_insert(heap_t *h, int value);
bool heap_extract_min(heap_t *h, int *out_value);
bool heap_peek_min(const heap_t *h, int *out_value);

size_t heap_size(const heap_t *h);
bool heap_is_empty(const heap_t *h);

/** Build a min-heap from an existing array in O(n). The array is reordered in place. */
void heap_build_min(int *arr, size_t n);

/** Sift-down at index `i` for an n-element array — exposed for heap sort. */
void heap_sift_down_max(int *arr, size_t i, size_t n);

#endif /* HEAP_H */
