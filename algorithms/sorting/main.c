/**
 * @file main.c
 * @brief Interactive demonstration of selection sort algorithm
 *
 * This program demonstrates the selection sort algorithm by allowing
 * users to input words and see them sorted alphabetically.
 */

#include "selection_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

void print_usage(void) {
  printf("Selection Sort Demo\n");
  printf("==================\n\n");
  printf("This program sorts words alphabetically using selection sort.\n\n");
}

void print_array(char **arr, size_t n, const char *label) {
  printf("%s: [", label);
  for (size_t i = 0; i < n; i++) {
    printf("\"%s\"", arr[i]);
    if (i < n - 1)
      printf(", ");
  }
  printf("]\n");
}

int main(int argc, char *argv[]) {
  // Check if words were passed as command-line arguments
  if (argc > 1) {
    char **words = &argv[1];
    size_t n = argc - 1;

    print_array(words, n, "Before");
    selection_sort_strings(words, n);
    print_array(words, n, "After ");

    return EXIT_SUCCESS;
  }

  // Interactive mode
  print_usage();

  char *words[MAX_WORDS];
  size_t count = 0;
  char buffer[MAX_WORD_LEN];

  printf("Enter words (one per line, empty line to finish):\n");

  while (count < MAX_WORDS) {
    printf("> ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
      break;

    // Remove newline
    buffer[strcspn(buffer, "\n")] = '\0';

    // Empty line signals end of input
    if (strlen(buffer) == 0)
      break;

    // Allocate and copy word
    words[count] = strdup(buffer);
    if (words[count] == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }
    count++;
  }

  if (count == 0) {
    printf("No words entered.\n");
    return EXIT_SUCCESS;
  }

  printf("\n");
  print_array(words, count, "Before");

  selection_sort_strings(words, count);

  print_array(words, count, "After ");

  // Free allocated memory
  for (size_t i = 0; i < count; i++) {
    free(words[i]);
  }

  return EXIT_SUCCESS;
}
