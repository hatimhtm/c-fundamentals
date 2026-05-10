/**
 * @file linked_list.h
 * @brief Singly-linked list of `int`.
 *
 * Designed for clarity over performance. Owns its nodes — `ll_destroy`
 * frees every node. Caller never touches the node struct directly; all
 * operations go through the list handle.
 *
 * | Operation       | Time |
 * |-----------------|------|
 * | push_front      | O(1) |
 * | push_back       | O(n) (no tail pointer cached) |
 * | pop_front       | O(1) |
 * | find            | O(n) |
 * | size            | O(1) (cached) |
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stddef.h>

typedef struct ll_node {
  int value;
  struct ll_node *next;
} ll_node_t;

typedef struct {
  ll_node_t *head;
  size_t size;
} linked_list_t;

linked_list_t *ll_create(void);
void ll_destroy(linked_list_t *list);

bool ll_push_front(linked_list_t *list, int value);
bool ll_push_back(linked_list_t *list, int value);
bool ll_pop_front(linked_list_t *list, int *out_value);

/** Returns the index of `value`, or `(size_t)-1` if missing. */
size_t ll_find(const linked_list_t *list, int value);
size_t ll_size(const linked_list_t *list);
bool ll_is_empty(const linked_list_t *list);

/** Reverses the list in place. O(n). */
void ll_reverse(linked_list_t *list);

#define LL_NOT_FOUND ((size_t)-1)

#endif /* LINKED_LIST_H */
