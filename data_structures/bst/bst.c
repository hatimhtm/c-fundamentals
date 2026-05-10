/**
 * @file bst.c
 *
 * Plain binary search tree, no rebalancing. Sufficient for teaching
 * the recursive structure; production code would reach for a red-black
 * tree or AVL.
 */

#include "bst.h"
#include <stdlib.h>

typedef struct bst_node {
  int value;
  struct bst_node *left;
  struct bst_node *right;
} bst_node_t;

struct bst {
  bst_node_t *root;
  size_t size;
};

bst_t *bst_create(void) {
  bst_t *t = malloc(sizeof(*t));
  if (!t) return NULL;
  t->root = NULL;
  t->size = 0;
  return t;
}

static void destroy_subtree(bst_node_t *n) {
  if (!n) return;
  destroy_subtree(n->left);
  destroy_subtree(n->right);
  free(n);
}

void bst_destroy(bst_t *t) {
  if (!t) return;
  destroy_subtree(t->root);
  free(t);
}

static bst_node_t *make_node(int v) {
  bst_node_t *n = malloc(sizeof(*n));
  if (!n) return NULL;
  n->value = v;
  n->left = n->right = NULL;
  return n;
}

bool bst_insert(bst_t *t, int value) {
  if (!t) return false;
  if (!t->root) {
    t->root = make_node(value);
    if (!t->root) return false;
    t->size = 1;
    return true;
  }
  bst_node_t *cur = t->root;
  while (1) {
    if (value < cur->value) {
      if (!cur->left) {
        cur->left = make_node(value);
        if (!cur->left) return false;
        t->size++;
        return true;
      }
      cur = cur->left;
    } else if (value > cur->value) {
      if (!cur->right) {
        cur->right = make_node(value);
        if (!cur->right) return false;
        t->size++;
        return true;
      }
      cur = cur->right;
    } else {
      return true; /* duplicate — silently ignore */
    }
  }
}

bool bst_contains(const bst_t *t, int value) {
  if (!t) return false;
  const bst_node_t *cur = t->root;
  while (cur) {
    if      (value < cur->value) cur = cur->left;
    else if (value > cur->value) cur = cur->right;
    else                          return true;
  }
  return false;
}

bool bst_min(const bst_t *t, int *out_value) {
  if (!t || !t->root) return false;
  const bst_node_t *cur = t->root;
  while (cur->left) cur = cur->left;
  if (out_value) *out_value = cur->value;
  return true;
}

bool bst_max(const bst_t *t, int *out_value) {
  if (!t || !t->root) return false;
  const bst_node_t *cur = t->root;
  while (cur->right) cur = cur->right;
  if (out_value) *out_value = cur->value;
  return true;
}

size_t bst_size(const bst_t *t) { return t ? t->size : 0; }

static void in_order_recursive(const bst_node_t *n,
                               void (*visit)(int, void *),
                               void *ctx) {
  if (!n) return;
  in_order_recursive(n->left, visit, ctx);
  visit(n->value, ctx);
  in_order_recursive(n->right, visit, ctx);
}

void bst_in_order(const bst_t *t,
                  void (*visit)(int, void *),
                  void *ctx) {
  if (!t || !visit) return;
  in_order_recursive(t->root, visit, ctx);
}
