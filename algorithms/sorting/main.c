/**
 * @file main.c
 * @brief Sorting CLI — pick an algorithm, sort either argv or stdin.
 *
 * Usage:
 *   sorting [--algo=NAME] [words ...]
 *   echo -e "banana\napple\ncherry" | sorting [--algo=NAME]
 *
 * NAME ∈ {selection, insertion, bubble, quick, merge}. Default: selection.
 */

#include "sorts.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1024
#define MAX_WORD_LEN 256

typedef void (*string_sort_fn)(char **, size_t);

static string_sort_fn algo_from_name(const char *name) {
  if (strcmp(name, "selection") == 0) return selection_sort_strings;
  if (strcmp(name, "insertion") == 0) return insertion_sort_strings;
  if (strcmp(name, "bubble") == 0)    return bubble_sort_strings;
  if (strcmp(name, "quick") == 0)     return quicksort_strings;
  if (strcmp(name, "merge") == 0)     return merge_sort_strings;
  if (strcmp(name, "heap") == 0)      return heap_sort_strings;
  /* radix is integers-only — not exposed via this string-sort CLI. */
  return NULL;
}

static void print_usage(const char *prog) {
  printf("Usage: %s [--algo=NAME] [words...]\n", prog);
  printf("\nAlgorithms: selection · insertion · bubble · quick · merge · heap\n");
  printf("Default: selection. Radix is integers-only and not exposed here.\n\n");
  printf("Examples:\n");
  printf("  %s banana apple cherry\n", prog);
  printf("  %s --algo=quick zebra ant mouse cat\n", prog);
  printf("  echo -e 'foo\\nbar\\nbaz' | %s --algo=merge\n", prog);
}

static void print_array(char **arr, size_t n, const char *label) {
  printf("%s: [", label);
  for (size_t i = 0; i < n; i++) {
    printf("\"%s\"", arr[i]);
    if (i + 1 < n) printf(", ");
  }
  printf("]\n");
}

int main(int argc, char *argv[]) {
  string_sort_fn sort = selection_sort_strings;
  const char *algo_name = "selection";

  /* Parse leading --algo=NAME flag. */
  int first_word = 1;
  if (argc > 1 && strncmp(argv[1], "--algo=", 7) == 0) {
    algo_name = argv[1] + 7;
    sort = algo_from_name(algo_name);
    if (!sort) {
      fprintf(stderr, "unknown algorithm: %s\n", algo_name);
      print_usage(argv[0]);
      return EXIT_FAILURE;
    }
    first_word = 2;
  } else if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
    print_usage(argv[0]);
    return EXIT_SUCCESS;
  }

  /* Source 1: command-line arguments after the optional flag. */
  if (argc > first_word) {
    char **words = &argv[first_word];
    size_t n = (size_t)(argc - first_word);
    print_array(words, n, "Before");
    sort(words, n);
    print_array(words, n, "After ");
    printf("Algorithm: %s\n", algo_name);
    return EXIT_SUCCESS;
  }

  /* Source 2: stdin (one word per line). */
  char *words[MAX_WORDS];
  size_t count = 0;
  char buffer[MAX_WORD_LEN];

  while (count < MAX_WORDS && fgets(buffer, sizeof(buffer), stdin)) {
    buffer[strcspn(buffer, "\n")] = '\0';
    if (buffer[0] == '\0') continue;
    words[count] = strdup(buffer);
    if (!words[count]) {
      fprintf(stderr, "Memory allocation failed\n");
      return EXIT_FAILURE;
    }
    count++;
  }

  if (count == 0) {
    print_usage(argv[0]);
    return EXIT_SUCCESS;
  }

  print_array(words, count, "Before");
  sort(words, count);
  print_array(words, count, "After ");
  printf("Algorithm: %s\n", algo_name);

  for (size_t i = 0; i < count; i++) free(words[i]);
  return EXIT_SUCCESS;
}
