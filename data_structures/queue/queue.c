/**
 * @file queue.c
 *
 * Circular buffer with head + size. We use head + size (not head + tail)
 * so an empty queue and a full queue are distinguishable without
 * sacrificing one slot.
 */

#include "queue.h"
#include <stdlib.h>
#include <string.h>

#define QUEUE_INITIAL_CAP 16

struct queue {
  int *data;
  size_t head;
  size_t size;
  size_t capacity;
};

queue_t *queue_create(void) {
  queue_t *q = malloc(sizeof(*q));
  if (!q) return NULL;
  q->data = malloc(QUEUE_INITIAL_CAP * sizeof(int));
  if (!q->data) { free(q); return NULL; }
  q->head = 0;
  q->size = 0;
  q->capacity = QUEUE_INITIAL_CAP;
  return q;
}

void queue_destroy(queue_t *q) {
  if (!q) return;
  free(q->data);
  free(q);
}

static bool queue_grow(queue_t *q) {
  size_t new_cap = q->capacity * 2;
  int *grown = malloc(new_cap * sizeof(int));
  if (!grown) return false;
  /* Linearise: copy head..end then 0..head into the new buffer. */
  for (size_t i = 0; i < q->size; i++) {
    grown[i] = q->data[(q->head + i) % q->capacity];
  }
  free(q->data);
  q->data = grown;
  q->head = 0;
  q->capacity = new_cap;
  return true;
}

bool queue_enqueue(queue_t *q, int value) {
  if (!q) return false;
  if (q->size == q->capacity && !queue_grow(q)) return false;
  size_t tail = (q->head + q->size) % q->capacity;
  q->data[tail] = value;
  q->size++;
  return true;
}

bool queue_dequeue(queue_t *q, int *out_value) {
  if (!q || q->size == 0) return false;
  if (out_value) *out_value = q->data[q->head];
  q->head = (q->head + 1) % q->capacity;
  q->size--;
  return true;
}

bool queue_peek(const queue_t *q, int *out_value) {
  if (!q || q->size == 0) return false;
  if (out_value) *out_value = q->data[q->head];
  return true;
}

size_t queue_size(const queue_t *q) { return q ? q->size : 0; }
bool queue_is_empty(const queue_t *q) { return !q || q->size == 0; }
