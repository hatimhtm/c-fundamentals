/**
 * @file trie.c
 */

#include "trie.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie_node {
  struct trie_node *children[26];
  bool terminal;
} trie_node_t;

struct trie {
  trie_node_t *root;
};

static trie_node_t *node_create(void) {
  return calloc(1, sizeof(trie_node_t));
}

static void node_destroy(trie_node_t *n) {
  if (!n) return;
  for (int i = 0; i < 26; i++) node_destroy(n->children[i]);
  free(n);
}

trie_t *trie_create(void) {
  trie_t *t = malloc(sizeof(*t));
  if (!t) return NULL;
  t->root = node_create();
  if (!t->root) { free(t); return NULL; }
  return t;
}

void trie_destroy(trie_t *t) {
  if (!t) return;
  node_destroy(t->root);
  free(t);
}

static int idx_of(char c) {
  unsigned char u = (unsigned char)c;
  if (u >= 'a' && u <= 'z') return u - 'a';
  return -1;
}

bool trie_insert(trie_t *t, const char *word) {
  if (!t || !word) return false;
  trie_node_t *cur = t->root;
  for (size_t i = 0; word[i] != '\0'; i++) {
    int j = idx_of(word[i]);
    if (j < 0) return false;
    if (!cur->children[j]) {
      cur->children[j] = node_create();
      if (!cur->children[j]) return false;
    }
    cur = cur->children[j];
  }
  cur->terminal = true;
  return true;
}

static const trie_node_t *walk(const trie_t *t, const char *s) {
  if (!t || !s) return NULL;
  const trie_node_t *cur = t->root;
  for (size_t i = 0; s[i] != '\0'; i++) {
    int j = idx_of(s[i]);
    if (j < 0 || !cur->children[j]) return NULL;
    cur = cur->children[j];
  }
  return cur;
}

bool trie_contains(const trie_t *t, const char *word) {
  const trie_node_t *n = walk(t, word);
  return n && n->terminal;
}

bool trie_starts_with(const trie_t *t, const char *prefix) {
  return walk(t, prefix) != NULL;
}
