/**
 * @file hash_table.h
 * @brief Open-addressing string→int hash table with linear probing.
 *
 * Open addressing was chosen over separate chaining for cache locality
 * and zero per-entry malloc churn. Linear probing in particular keeps
 * the math simple; the load factor is capped at 0.75 with auto-resize.
 *
 * Hash function: djb2 (k=33) — fast, good enough for non-adversarial data.
 *
 * | Operation       | Avg     | Worst   |
 * |-----------------|---------|---------|
 * | get             | O(1)    | O(n)    |
 * | set             | O(1)    | O(n)    |
 * | remove          | O(1)    | O(n)    |
 * | resize (rehash) | O(n)    | (amortized into set) |
 */

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>
#include <stddef.h>

typedef struct hash_table hash_table_t;

hash_table_t *ht_create(void);
void ht_destroy(hash_table_t *ht);

/** Inserts or updates `key` → `value`. Returns false on allocation failure. */
bool ht_set(hash_table_t *ht, const char *key, int value);

/** Writes `*out` and returns true if found, otherwise false. */
bool ht_get(const hash_table_t *ht, const char *key, int *out);

bool ht_remove(hash_table_t *ht, const char *key);
bool ht_contains(const hash_table_t *ht, const char *key);

size_t ht_size(const hash_table_t *ht);
size_t ht_capacity(const hash_table_t *ht);

#endif /* HASH_TABLE_H */
