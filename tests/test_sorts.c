/**
 * @file test_sorts.c
 * @brief Tests for all five sort algorithms (string + int variants).
 */

#include "../algorithms/sorting/sorts.h"
#include "test.h"
#include <stdlib.h>
#include <string.h>

typedef void (*int_sort_fn)(int *, size_t);
typedef void (*str_sort_fn)(char **, size_t);

static int int_array_eq(const int *a, const int *b, size_t n) {
  for (size_t i = 0; i < n; i++) if (a[i] != b[i]) return 0;
  return 1;
}

static int str_array_eq(char **a, char **b, size_t n) {
  for (size_t i = 0; i < n; i++) if (strcmp(a[i], b[i]) != 0) return 0;
  return 1;
}

static void check_int_sort(int_sort_fn fn) {
  int input[]    = {5, 2, 9, 1, 5, 6, 7, 3};
  int expected[] = {1, 2, 3, 5, 5, 6, 7, 9};
  size_t n = sizeof(input) / sizeof(int);
  fn(input, n);
  ASSERT_TRUE(int_array_eq(input, expected, n));
}

static void check_str_sort(str_sort_fn fn) {
  char *a = "banana", *b = "apple", *c = "cherry", *d = "date";
  char *input[] = {a, b, c, d};
  char *expected[] = {b, a, c, d}; /* alphabetical: apple, banana, cherry, date */
  fn(input, 4);
  ASSERT_TRUE(str_array_eq(input, expected, 4));
}

TEST_CASE(selection_sort_int) { check_int_sort(selection_sort_ints); }
TEST_CASE(selection_sort_str) { check_str_sort(selection_sort_strings); }
TEST_CASE(insertion_sort_int) { check_int_sort(insertion_sort_ints); }
TEST_CASE(insertion_sort_str) { check_str_sort(insertion_sort_strings); }
TEST_CASE(bubble_sort_int)    { check_int_sort(bubble_sort_ints); }
TEST_CASE(bubble_sort_str)    { check_str_sort(bubble_sort_strings); }
TEST_CASE(quicksort_int)      { check_int_sort(quicksort_ints); }
TEST_CASE(quicksort_str)      { check_str_sort(quicksort_strings); }
TEST_CASE(merge_sort_int)     { check_int_sort(merge_sort_ints); }
TEST_CASE(merge_sort_str)     { check_str_sort(merge_sort_strings); }

TEST_CASE(empty_arrays) {
  int empty[1];
  selection_sort_ints(empty, 0);
  insertion_sort_ints(empty, 0);
  bubble_sort_ints(empty, 0);
  quicksort_ints(empty, 0);
  merge_sort_ints(empty, 0);
  ASSERT_TRUE(1); /* no crash on n=0 */
}

TEST_CASE(single_element) {
  int single[] = {42};
  quicksort_ints(single, 1);
  ASSERT_EQ_INT(single[0], 42);
}

TEST_CASE(already_sorted) {
  int sorted[] = {1, 2, 3, 4, 5};
  int expected[] = {1, 2, 3, 4, 5};
  bubble_sort_ints(sorted, 5);
  ASSERT_TRUE(int_array_eq(sorted, expected, 5));
}

TEST_CASE(reverse_sorted) {
  int rev[] = {9, 7, 5, 3, 1};
  int expected[] = {1, 3, 5, 7, 9};
  quicksort_ints(rev, 5);
  ASSERT_TRUE(int_array_eq(rev, expected, 5));
}

void run_sort_tests(void) {
  RUN_TEST(selection_sort_int);
  RUN_TEST(selection_sort_str);
  RUN_TEST(insertion_sort_int);
  RUN_TEST(insertion_sort_str);
  RUN_TEST(bubble_sort_int);
  RUN_TEST(bubble_sort_str);
  RUN_TEST(quicksort_int);
  RUN_TEST(quicksort_str);
  RUN_TEST(merge_sort_int);
  RUN_TEST(merge_sort_str);
  RUN_TEST(empty_arrays);
  RUN_TEST(single_element);
  RUN_TEST(already_sorted);
  RUN_TEST(reverse_sorted);
}
