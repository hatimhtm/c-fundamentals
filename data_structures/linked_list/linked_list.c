/**
 * @file linked_list.c
 */

#include "linked_list.h"
#include <stdlib.h>

linked_list_t *ll_create(void) {
  linked_list_t *list = malloc(sizeof(*list));
  if (!list) return NULL;
  list->head = NULL;
  list->size = 0;
  return list;
}

void ll_destroy(linked_list_t *list) {
  if (!list) return;
  ll_node_t *cur = list->head;
  while (cur) {
    ll_node_t *next = cur->next;
    free(cur);
    cur = next;
  }
  free(list);
}

bool ll_push_front(linked_list_t *list, int value) {
  if (!list) return false;
  ll_node_t *node = malloc(sizeof(*node));
  if (!node) return false;
  node->value = value;
  node->next = list->head;
  list->head = node;
  list->size++;
  return true;
}

bool ll_push_back(linked_list_t *list, int value) {
  if (!list) return false;
  ll_node_t *node = malloc(sizeof(*node));
  if (!node) return false;
  node->value = value;
  node->next = NULL;

  if (!list->head) {
    list->head = node;
  } else {
    ll_node_t *cur = list->head;
    while (cur->next) cur = cur->next;
    cur->next = node;
  }
  list->size++;
  return true;
}

bool ll_pop_front(linked_list_t *list, int *out_value) {
  if (!list || !list->head) return false;
  ll_node_t *node = list->head;
  if (out_value) *out_value = node->value;
  list->head = node->next;
  free(node);
  list->size--;
  return true;
}

size_t ll_find(const linked_list_t *list, int value) {
  if (!list) return LL_NOT_FOUND;
  size_t idx = 0;
  for (ll_node_t *cur = list->head; cur; cur = cur->next, idx++) {
    if (cur->value == value) return idx;
  }
  return LL_NOT_FOUND;
}

size_t ll_size(const linked_list_t *list) {
  return list ? list->size : 0;
}

bool ll_is_empty(const linked_list_t *list) {
  return !list || list->size == 0;
}

void ll_reverse(linked_list_t *list) {
  if (!list) return;
  ll_node_t *prev = NULL;
  ll_node_t *cur = list->head;
  while (cur) {
    ll_node_t *next = cur->next;
    cur->next = prev;
    prev = cur;
    cur = next;
  }
  list->head = prev;
}
