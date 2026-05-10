/**
 * @file queue.h
 * @brief FIFO queue of `int`, backed by a circular buffer.
 *
 * Circular buffer beats a linked list here: O(1) push/pop with a single
 * malloc per resize, no per-element allocation. Doubles when full.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct queue queue_t;

queue_t *queue_create(void);
void queue_destroy(queue_t *q);

bool queue_enqueue(queue_t *q, int value);
bool queue_dequeue(queue_t *q, int *out_value);
bool queue_peek(const queue_t *q, int *out_value);

size_t queue_size(const queue_t *q);
bool queue_is_empty(const queue_t *q);

#endif /* QUEUE_H */
