/**
 * @file heap.c
 */

#include "heap.h"
#include <stdlib.h>

#define HEAP_INITIAL_CAP 16

struct heap {
  int *data;
  size_t size;
  size_t capacity;
};

static void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

heap_t *heap_create(void) {
  heap_t *h = malloc(sizeof(*h));
  if (!h) return NULL;
  h->data = malloc(HEAP_INITIAL_CAP * sizeof(int));
  if (!h->data) { free(h); return NULL; }
  h->size = 0;
  h->capacity = HEAP_INITIAL_CAP;
  return h;
}

void heap_destroy(heap_t *h) {
  if (!h) return;
  free(h->data);
  free(h);
}

static bool heap_grow(heap_t *h) {
  size_t new_cap = h->capacity * 2;
  int *grown = realloc(h->data, new_cap * sizeof(int));
  if (!grown) return false;
  h->data = grown;
  h->capacity = new_cap;
  return true;
}

static void sift_up_min(int *arr, size_t i) {
  while (i > 0) {
    size_t parent = (i - 1) / 2;
    if (arr[parent] <= arr[i]) break;
    swap(&arr[parent], &arr[i]);
    i = parent;
  }
}

static void sift_down_min(int *arr, size_t i, size_t n) {
  while (1) {
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t smallest = i;
    if (left < n && arr[left] < arr[smallest]) smallest = left;
    if (right < n && arr[right] < arr[smallest]) smallest = right;
    if (smallest == i) break;
    swap(&arr[i], &arr[smallest]);
    i = smallest;
  }
}

bool heap_insert(heap_t *h, int value) {
  if (!h) return false;
  if (h->size == h->capacity && !heap_grow(h)) return false;
  h->data[h->size] = value;
  sift_up_min(h->data, h->size);
  h->size++;
  return true;
}

bool heap_extract_min(heap_t *h, int *out_value) {
  if (!h || h->size == 0) return false;
  if (out_value) *out_value = h->data[0];
  h->size--;
  if (h->size > 0) {
    h->data[0] = h->data[h->size];
    sift_down_min(h->data, 0, h->size);
  }
  return true;
}

bool heap_peek_min(const heap_t *h, int *out_value) {
  if (!h || h->size == 0) return false;
  if (out_value) *out_value = h->data[0];
  return true;
}

size_t heap_size(const heap_t *h) { return h ? h->size : 0; }
bool heap_is_empty(const heap_t *h) { return !h || h->size == 0; }

void heap_build_min(int *arr, size_t n) {
  if (n <= 1) return;
  /* Floyd's algorithm: sift-down from the last non-leaf node back to root. */
  for (size_t i = n / 2; i > 0; i--) {
    sift_down_min(arr, i - 1, n);
  }
}

/* Max-heap sift-down (used by heap_sort_ints). */
void heap_sift_down_max(int *arr, size_t i, size_t n) {
  while (1) {
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;
    size_t largest = i;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest == i) break;
    swap(&arr[i], &arr[largest]);
    i = largest;
  }
}
