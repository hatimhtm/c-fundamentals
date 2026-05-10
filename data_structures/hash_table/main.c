/**
 * @file main.c
 * @brief Hash-table CLI demo — word frequency counter.
 */

#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <word1> <word2> ...\n", argv[0]);
    printf("Counts occurrences of each word.\n");
    printf("Example: %s the quick brown fox the lazy dog the\n", argv[0]);
    return EXIT_FAILURE;
  }

  hash_table_t *ht = ht_create();
  if (!ht) return EXIT_FAILURE;

  for (int i = 1; i < argc; i++) {
    int current = 0;
    ht_get(ht, argv[i], &current);
    if (!ht_set(ht, argv[i], current + 1)) {
      fprintf(stderr, "out of memory\n");
      ht_destroy(ht);
      return EXIT_FAILURE;
    }
  }

  printf("Counts (size=%zu, capacity=%zu):\n",
         ht_size(ht), ht_capacity(ht));
  for (int i = 1; i < argc; i++) {
    int count = 0;
    if (ht_get(ht, argv[i], &count)) {
      printf("  %-20s %d\n", argv[i], count);
      ht_remove(ht, argv[i]); /* dedup the printout */
    }
  }

  ht_destroy(ht);
  return EXIT_SUCCESS;
}
