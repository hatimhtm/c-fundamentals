/**
 * @file bst.h
 * @brief Binary search tree of `int` (no balancing — O(log n) average,
 *        O(n) worst-case on sorted input).
 *
 * Operations:
 * | op           | average  | worst    |
 * |--------------|----------|----------|
 * | insert       | O(log n) | O(n)     |
 * | contains     | O(log n) | O(n)     |
 * | min / max    | O(log n) | O(n)     |
 * | in_order     | O(n)     | O(n)     |
 */

#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct bst bst_t;

bst_t *bst_create(void);
void bst_destroy(bst_t *t);

/** Inserts `value`. Duplicates are ignored. Returns true on success. */
bool bst_insert(bst_t *t, int value);

bool bst_contains(const bst_t *t, int value);

bool bst_min(const bst_t *t, int *out_value);
bool bst_max(const bst_t *t, int *out_value);

size_t bst_size(const bst_t *t);

/** Visits every node in ascending order, calling `visit` on each value. */
void bst_in_order(const bst_t *t, void (*visit)(int value, void *ctx), void *ctx);

#endif /* BST_H */
