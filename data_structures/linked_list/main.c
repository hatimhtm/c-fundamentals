/**
 * @file main.c
 * @brief Linked-list CLI demo.
 *
 * Reads numbers from argv, builds a list (push_back), prints it, finds
 * the first arg, reverses, prints again. Demonstrates all the core ops.
 */

#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

static void print_list(const linked_list_t *list, const char *label) {
  printf("%s (size=%zu): [", label, ll_size(list));
  for (const ll_node_t *cur = list->head; cur; cur = cur->next) {
    printf("%d", cur->value);
    if (cur->next) printf(" → ");
  }
  printf("]\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <num1> <num2> ...\n", argv[0]);
    printf("Example: %s 1 2 3 4 5\n", argv[0]);
    return EXIT_FAILURE;
  }

  linked_list_t *list = ll_create();
  if (!list) return EXIT_FAILURE;

  for (int i = 1; i < argc; i++) {
    if (!ll_push_back(list, atoi(argv[i]))) {
      fprintf(stderr, "out of memory\n");
      ll_destroy(list);
      return EXIT_FAILURE;
    }
  }

  print_list(list, "Built");

  int target = atoi(argv[1]);
  size_t idx = ll_find(list, target);
  if (idx == LL_NOT_FOUND) {
    printf("find(%d): not found\n", target);
  } else {
    printf("find(%d): index %zu\n", target, idx);
  }

  ll_reverse(list);
  print_list(list, "Reversed");

  ll_destroy(list);
  return EXIT_SUCCESS;
}
