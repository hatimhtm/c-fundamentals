/**
 * @file trie.h
 * @brief Prefix tree (trie) over lowercase ASCII letters a-z.
 *
 * 26-way fixed branching, one node per inserted prefix. Memory cost is
 * proportional to the union of all prefixes — heavier than a hash set
 * but supports starts_with (prefix queries) in O(prefix length).
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

typedef struct trie trie_t;

trie_t *trie_create(void);
void trie_destroy(trie_t *t);

/** Inserts a lowercase a-z word. Returns false on allocation failure or
 *  if the word contains a non-{a-z} character. */
bool trie_insert(trie_t *t, const char *word);

bool trie_contains(const trie_t *t, const char *word);

/** True if any inserted word begins with `prefix`. */
bool trie_starts_with(const trie_t *t, const char *prefix);

#endif /* TRIE_H */
