/**
 * @file hash_table.c
 *
 * Open-addressing hash table with linear probing and tombstone deletion.
 * Capacity is a power of two so we can replace `% capacity` with a mask.
 */

#include "hash_table.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HT_INITIAL_CAPACITY 16
#define HT_MAX_LOAD 0.75

typedef enum { SLOT_EMPTY, SLOT_OCCUPIED, SLOT_TOMBSTONE } slot_state_t;

typedef struct {
  char *key;
  int value;
  slot_state_t state;
} ht_slot_t;

struct hash_table {
  ht_slot_t *slots;
  size_t capacity; /* power of two */
  size_t size;     /* number of OCCUPIED slots */
};

/* djb2 — Daniel J. Bernstein. Multiply-by-33 with seed 5381. */
static uint64_t djb2(const char *s) {
  uint64_t h = 5381;
  int c;
  while ((c = (unsigned char)*s++)) h = ((h << 5) + h) + (uint64_t)c;
  return h;
}

static bool ht_resize(hash_table_t *ht, size_t new_cap);

hash_table_t *ht_create(void) {
  hash_table_t *ht = malloc(sizeof(*ht));
  if (!ht) return NULL;
  ht->capacity = HT_INITIAL_CAPACITY;
  ht->size = 0;
  ht->slots = calloc(ht->capacity, sizeof(*ht->slots));
  if (!ht->slots) { free(ht); return NULL; }
  return ht;
}

void ht_destroy(hash_table_t *ht) {
  if (!ht) return;
  for (size_t i = 0; i < ht->capacity; i++) {
    if (ht->slots[i].state == SLOT_OCCUPIED) free(ht->slots[i].key);
  }
  free(ht->slots);
  free(ht);
}

/** Returns the slot index for `key` (insert position or existing match). */
static size_t probe(const ht_slot_t *slots, size_t cap, const char *key) {
  size_t mask = cap - 1;
  size_t i = (size_t)djb2(key) & mask;
  size_t first_tombstone = (size_t)-1;

  while (slots[i].state != SLOT_EMPTY) {
    if (slots[i].state == SLOT_OCCUPIED && strcmp(slots[i].key, key) == 0) {
      return i;
    }
    if (slots[i].state == SLOT_TOMBSTONE && first_tombstone == (size_t)-1) {
      first_tombstone = i;
    }
    i = (i + 1) & mask;
  }
  return first_tombstone == (size_t)-1 ? i : first_tombstone;
}

bool ht_set(hash_table_t *ht, const char *key, int value) {
  if (!ht || !key) return false;

  if ((double)(ht->size + 1) / (double)ht->capacity > HT_MAX_LOAD) {
    if (!ht_resize(ht, ht->capacity * 2)) return false;
  }

  size_t i = probe(ht->slots, ht->capacity, key);
  if (ht->slots[i].state == SLOT_OCCUPIED) {
    ht->slots[i].value = value;
    return true;
  }

  char *dup = strdup(key);
  if (!dup) return false;
  ht->slots[i].key = dup;
  ht->slots[i].value = value;
  ht->slots[i].state = SLOT_OCCUPIED;
  ht->size++;
  return true;
}

bool ht_get(const hash_table_t *ht, const char *key, int *out) {
  if (!ht || !key) return false;
  size_t i = probe(ht->slots, ht->capacity, key);
  if (ht->slots[i].state != SLOT_OCCUPIED) return false;
  if (out) *out = ht->slots[i].value;
  return true;
}

bool ht_remove(hash_table_t *ht, const char *key) {
  if (!ht || !key) return false;
  size_t i = probe(ht->slots, ht->capacity, key);
  if (ht->slots[i].state != SLOT_OCCUPIED) return false;
  free(ht->slots[i].key);
  ht->slots[i].key = NULL;
  ht->slots[i].state = SLOT_TOMBSTONE;
  ht->size--;
  return true;
}

bool ht_contains(const hash_table_t *ht, const char *key) {
  return ht_get(ht, key, NULL);
}

size_t ht_size(const hash_table_t *ht) { return ht ? ht->size : 0; }
size_t ht_capacity(const hash_table_t *ht) { return ht ? ht->capacity : 0; }

static bool ht_resize(hash_table_t *ht, size_t new_cap) {
  ht_slot_t *new_slots = calloc(new_cap, sizeof(*new_slots));
  if (!new_slots) return false;

  /* Rehash: struct-copy occupied slots into new_slots — the key pointer is
     transferred (no realloc), tombstones are dropped on the floor. */
  for (size_t i = 0; i < ht->capacity; i++) {
    if (ht->slots[i].state == SLOT_OCCUPIED) {
      size_t j = probe(new_slots, new_cap, ht->slots[i].key);
      new_slots[j] = ht->slots[i];
    }
  }
  free(ht->slots);
  ht->slots = new_slots;
  ht->capacity = new_cap;
  return true;
}
